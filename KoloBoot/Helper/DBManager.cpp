//
//  DBManager.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "DBManager.hpp"
#include "helper_oncpp.h"
#include <iostream>

DBManager::DBManager() {
    dbase = new SQLite::Database(Koloboot::Helper::fileBundleLocation("koloboot.db"));
}

DBManager::~DBManager() {
    if (dbase != nullptr) {
        delete dbase;
    }
}

std::function<int()> DBManager::countDataProject() {
    return [&]() -> int
    {
        try {
            SQLite::Statement query(*dbase, "select count(id_project) as hit from projects");
            while (query.executeStep()) {
                int hit = query.getColumn(0);
                return hit;
            }
            
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return 0;
    };
}

std::function<int(const Model::Project&)> DBManager::saveProject() {
    return [&](const Model::Project& proj) -> int
    {
        try {
            SQLite::Statement query(*dbase, "insert into project(name, base_url) values(?, ?)");
            query.bind(1, proj.getName());
            query.bind(2, proj.getBaseUrl());
            return query.exec();
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return 0;
    };
}
