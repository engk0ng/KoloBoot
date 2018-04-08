//
//  firebase_database.cpp
//  KoloBoot
//
//  Created by Abu Salman on 23/11/17.
//  Copyright © 2017 KoloBoot. All rights reserved.
//

#include <CoreFoundation/CoreFoundation.h>
#include "firebase_database.h"
#include <sys/time.h>
#include <string>

using namespace firebase;
using namespace firebase::database;
using namespace Koloboot::Helper;

FirebaseDatabase::FirebaseDatabase(const void *cn): FirebaseBasic(cn, DATABASE) {
    
}

std::function<bool(const std::map<std::string, std::string> &)> FirebaseDatabase::saveProject() {
    return [&] (const std::map<std::string, std::string> &param) -> bool
    {
        Database *_db = get_database();
        DatabaseReference dbref = _db->GetReference();
        std::map<std::string, Variant> data = std::map<std::string, Variant>();
        std::string uuid = getUserDefault(CFSTR("UUID"));
        data["base_url"] = Variant(param.at("base_url"));
        data["name"] = Variant(param.at("nama"));
        auto tot = std::map<std::string, Variant>();
        tot["project"] = data;
        auto store = std::map<std::string, Variant>();
        store[uuid] = tot;
        dbref.UpdateChildren(store);
        return true;
    };
}
