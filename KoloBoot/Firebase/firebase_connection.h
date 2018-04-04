//
//  firebase_connection.hpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#ifndef firebase_connection_hpp
#define firebase_connection_hpp

#include <stdio.h>
#include <firebase/app.h>
#include <firebase/database.h>
#include "helper_oncpp.h"

class FirebaseConnection {
    
public:
    FirebaseConnection();
    ~FirebaseConnection();
    const void *get_connection(FirebaseType type);
private:
    firebase::App *app;
    firebase::database::Database *database = nullptr;
};

#endif /* firebase_connection_hpp */
