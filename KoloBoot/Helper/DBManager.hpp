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
#include "Path.hpp"
#include "Param.hpp"

typedef std::vector<Model::Param> DataParam;
typedef std::function<void(int)> PathSaveCallback;
typedef PathSaveCallback ProjectDeleteCallback;
typedef std::vector<Model::Path> DataPath;
typedef std::vector<Model::Project> DataProject;
typedef PathSaveCallback DeletePathCallback;
typedef std::function<void(Model::Project)> ProjectByIdCallback;
typedef std::function<void(DataParam)> DataParamByPath;

typedef std::function<int(const Model::Project&)> FuncProjectSave;
typedef std::function<DataProject()> FuncProjectGetAll;
typedef std::function<DataPath(int)> FuncPathGetByIdProj;

class DBManager {
    
public:
    DBManager();
    ~DBManager();
    std::function<int()> countDataProject();
    FuncProjectSave saveProject();
    void savePath(const Model::Path&, PathSaveCallback);
    FuncProjectGetAll getAllProject();
    FuncPathGetByIdProj getPathByIdProject();
    FuncProjectSave updateProject();
    void deleteProject(const Model::Project&, ProjectDeleteCallback);
    void deletePath(const Model::Path&, DeletePathCallback);
    void getProjectById(int, ProjectByIdCallback);
    void getAllParamByPath(int, DataParamByPath);
private:
    SQLite::Database *dbase;
};

#endif /* DBManager_hpp */
