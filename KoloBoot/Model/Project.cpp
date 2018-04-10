//
//  Project.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "Project.hpp"


namespace Model {
    Project::Project(): Model::BaseModel()
    {
    }
    
    Project::Project(int id, const std::string& name, const std::string& _base_url):
        Model::BaseModel(id, name),
        base_url(_base_url)
    {
    }
    
    Project::Project(const std::string& name, const std::string& _base_url):
        Model::BaseModel(name),
        base_url(_base_url)
    {
    }
    
    Project::~Project()
    {
    }
    
    void Project::setBaseUrl(const std::string &bs)
    {
        base_url = bs;
    }
    
    const std::string Project::getBaseUrl() const noexcept
    {
        return base_url;
    }
    
    std::ostream& Project::operator<<(std::ostream &os)
    {
        os << "[ ID : " << getId() << " Name: " << getName() << " BaseURL: " << getBaseUrl() << " ]" << std::endl;
        return os;
    }
    
    void Project::setPaths(const std::vector<Model::Path>& _paths) {
        paths = _paths;
    }
    
    std::vector<Model::Path> Project::getPaths() const noexcept {
        return paths;
    }
}
