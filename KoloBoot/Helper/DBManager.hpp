//
//  DBManager.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef DBManager_hpp
#define DBManager_hpp

#include <stdio.h>
#include <utility>
#include <functional>
#include "SQLiteCpp.h"
#include "Project.hpp"

class DBManager {
    
public:
    DBManager();
    ~DBManager();
    std::function<int()> countDataProject();
    std::function<int(const Model::Project&)> saveProject();
private:
    SQLite::Database *dbase;
};

#endif /* DBManager_hpp */
