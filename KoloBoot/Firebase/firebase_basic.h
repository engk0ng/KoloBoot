//
//  firebase_basic.hpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#ifndef firebase_basic_hpp
#define firebase_basic_hpp

#include <stdio.h>
#include <firebase/app.h>
#include <firebase/database.h>
#include "helper_oncpp.h"

class FirebaseBasic {
    
public:
    explicit FirebaseBasic(const void *ptr, FirebaseType type);
    ~FirebaseBasic();
protected:
    firebase::database::Database *get_database();
    void run_process(const firebase::FutureBase& future, const char *name);
private:
    firebase::database::Database *db;
};

#endif /* firebase_basic_hpp */
