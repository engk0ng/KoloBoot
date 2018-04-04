//
//  firebase_database.hpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#ifndef firebase_database_hpp
#define firebase_database_hpp

#include <stdio.h>
#include "firebase_basic.h"
#include "helper_oncpp.h"

class FirebaseDatabase: public FirebaseBasic {
    
public:
    FirebaseDatabase(const void *cn);
private:
};

#endif /* firebase_database_hpp */
