//
//  Path.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "Path.hpp"

namespace Model {
    Path::Path(int id_pth, int proj_id, const std::string& nm, const std::string& pth):
        Model::BaseModel(id_pth, nm),
        project_id(proj_id),
        path(pth)
    {
        
    }
    
    Path::Path(int proj_id, const std::string& nm, const std::string& pth):
        Model::BaseModel(nm),
        project_id(proj_id),
        path(pth)
    {
        
    }
    
    Path::Path()
    {
        
    }
    
    Path::~Path()
    {
        
    }
    
    void Path::setPath(const std::string &pth)
    {
        path = pth;
    }
    
    const std::string Path::getPath() const noexcept
    {
        return path;
    }
    
    void Path::setProjectId(int proj)
    {
        project_id = proj;
    }
    
    int Path::getProjectId() const noexcept
    {
        return project_id;
    }
}

