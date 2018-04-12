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

DBManager::DBManager()
{
    std::string pth = Koloboot::Helper::getUserDefault(CFSTR("DIR"));
    //std::cout << "Db: " << pth << std::endl;
    dbase = new SQLite::Database(pth, SQLite::OPEN_READWRITE);
}

DBManager::~DBManager()
{
    if (dbase != nullptr) {
        delete dbase;
    }
}

std::function<int()> DBManager::countDataProject()
{
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

FuncProjectSave DBManager::saveProject()
{
    return [&](const Model::Project& proj) -> int
    {
        try {
            SQLite::Statement query(*dbase, "insert into projects(name, base_url) values(?, ?)");
            query.bind(1, proj.getName());
            query.bind(2, proj.getBaseUrl());
            if (query.exec() != 0) {
                return static_cast<int>(dbase->getLastInsertRowid());
            }
            else {
                return 0;
            }
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return 0;
    };
}

void DBManager::savePath(const Model::Path &pth, PathSaveCallback callback)
{
    try {
        SQLite::Statement query(*dbase, "insert into paths(project_id, name, path_url, type) values(?, ?, ?, ?)");
        query.bind(1, pth.getProjectId());
        query.bind(2, pth.getName());
        query.bind(3, pth.getPath());
        query.bind(4, pth.getType<std::string>());
        if (query.exec()) {
            callback(static_cast<int>(dbase->getLastInsertRowid()));
        }
        else {
            callback(0);
        }
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

FuncProjectGetAll DBManager::getAllProject() {
    return [&]() -> DataProject
    {
        DataProject result;
        try {
            SQLite::Statement query(*dbase, "select * from projects");
            while (query.executeStep()) {
                Model::Project proj;
                proj.setId(query.getColumn("id_project").getInt());
                proj.setName(query.getColumn("name").getString());
                auto dataPath = getPathByIdProject();
                proj.setPaths(dataPath(proj.getId()));
                proj.setBaseUrl(query.getColumn("base_url").getString());
                result.push_back(proj);
            }
            return result;
            
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return result;
    };
}

FuncPathGetByIdProj DBManager::getPathByIdProject() {
    return [&](int id_proj) -> DataPath
    {
        DataPath result;
        try {
            SQLite::Statement query(*dbase, "select * from paths where project_id = ?");
            query.bind(1, id_proj);
            while (query.executeStep()) {
                Model::Path path;
                path.setId(query.getColumn("id_path").getInt());
                path.setName(query.getColumn("name").getString());
                path.setPath(query.getColumn("path_url").getString());
                path.setType(query.getColumn("type").getString());
                path.setProjectId(query.getColumn("project_id").getInt());
                result.push_back(path);
            }
            return result;
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return result;
    };
}

FuncProjectSave DBManager::updateProject() {
    return [&](const Model::Project& proj) -> int
    {
        int result = 0;
        try {
            SQLite::Statement query(*dbase, "update projects set name = ?, base_url = ? where id_project = ?");
            query.bind(1, proj.getName());
            query.bind(2, proj.getBaseUrl());
            query.bind(3, proj.getId());
            result = query.exec();
        } catch (std::exception& ex) {
            std::cout << ex.what() << std::endl;
        }
        return result;
    };
}

void DBManager::deleteProject(const Model::Project &proj, ProjectDeleteCallback callback) {
    try {
        SQLite::Transaction trans(*dbase);
        std::string qry = "delete from projects where id_project = ";
        int nb = dbase->exec(qry + std::to_string(proj.getId()));
        if (nb == 1) {
            auto get_param = [&](int id_proj) -> int {
                int result = 0;
                SQLite::Statement query(*dbase, "select id_path from paths where project_id = ? limit 1");
                query.bind(1, id_proj);
                while (query.executeStep()) {
                    result = query.getColumn("id_path").getInt();
                }
                return result;
            };
            int id_path = get_param(proj.getId());
            if (id_path > 0) {
                std::string qry2 = "delete from paths where project_id = ";
                nb = dbase->exec(qry2 + std::to_string(proj.getId()));
            }
            auto count_param = [&](int id_pth) -> int {
                int result = 0;
                SQLite::Statement query(*dbase, "select count(id_param) as hit from param where path_id = ?");
                query.bind(1, id_pth);
                while (query.executeStep()) {
                    result = query.getColumn("hit").getInt();
                }
                return result;
            };
            int hit_param;
            if ((hit_param = count_param(id_path)) > 0) {
                std::string qry3 = "delete from param where path_id = ";
                nb = dbase->exec(qry3 + std::to_string(id_path));
            }
        }
        trans.commit();
        callback(nb);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void DBManager::deletePath(const Model::Path &pth, DeletePathCallback callback) {
    try {
        SQLite::Transaction trans(*dbase);
        std::string qry = "delete from paths where id_path = ";
        int nb = dbase->exec(qry + std::to_string(pth.getId()));
        if (nb == 1) {
            auto count_param = [&](int id_pth) -> int {
                int result = 0;
                SQLite::Statement query(*dbase, "select count(id_param) as hit from param where path_id = ?");
                query.bind(1, id_pth);
                while (query.executeStep()) {
                    result = query.getColumn("hit").getInt();
                }
                return result;
            };
            int hit = 0;
            if ((hit = count_param(pth.getId())) > 0) {
                std::string qry3 = "delete from param where path_id = ";
                nb = dbase->exec(qry3 + std::to_string(pth.getId()));
            }
        }
        trans.commit();
        callback(nb);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

void DBManager::getProjectById(int id, ProjectByIdCallback callback) {
    try {
        Model::Project result;
        SQLite::Statement query(*dbase, "select * from projects where id_project = ?");
        query.bind(1, id);
        while (query.executeStep()) {
            result.setBaseUrl(query.getColumn("base_url").getString());
            result.setId(id);
            result.setName(query.getColumn("name").getString());
        }
        callback(result);
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}
