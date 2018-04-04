//
//  firebase_connection.cpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#include "firebase_connection.h"

FirebaseConnection::FirebaseConnection() {
    app = firebase::App::Create();
    database = firebase::database::Database::GetInstance(app->GetInstance());
    database->set_persistence_enabled(true);
    printf("Created the firebase app %x",
           static_cast<int>(reinterpret_cast<intptr_t>(app)));
}

const void *FirebaseConnection::get_connection(FirebaseType type) {
    if (type == DATABASE) {
        return static_cast<void *>(database);
    }
    return nullptr;
}

FirebaseConnection::~FirebaseConnection() {
    delete database;
    database = nullptr;
    delete app;
    app = nullptr;
}
