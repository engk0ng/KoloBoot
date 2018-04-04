//
//  firebase_database.cpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#include "firebase_database.h"
#include <sys/time.h>

using namespace firebase;

FirebaseDatabase::FirebaseDatabase(const void *cn): FirebaseBasic(cn, DATABASE) {
    
}

