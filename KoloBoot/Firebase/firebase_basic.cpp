//
//  firebase_basic.cpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#include "firebase_basic.h"
#include <mutex>
#include <thread>

inline void WaitForCompletion(const firebase::FutureBase& future, const char* name) {
    std::mutex mtx;
    mtx.lock();
    while (future.status() == firebase::kFutureStatusPending) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    mtx.unlock();
    if (future.status() != firebase::kFutureStatusComplete) {
        printf("ERROR: %s returned an invalid result.", name);
    } else if (future.error() != 0) {
        printf("ERROR: %s returned error %d: %s", name, future.error(),
               future.error_message());
    }
}

FirebaseBasic::FirebaseBasic(const void *ptr, FirebaseType type) {
    if (type == DATABASE) {
        db = static_cast<firebase::database::Database *>(const_cast<void *>(ptr));
    }
}

FirebaseBasic::~FirebaseBasic() {
    
}

firebase::database::Database *FirebaseBasic::get_database() {
    return db;
}

void FirebaseBasic::run_process(const firebase::FutureBase &future, const char *name) {
    std::thread th(WaitForCompletion, future, name);
    th.join();
}

