//
//  Auth.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 13/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "Auth.hpp"

namespace Model {
    Auth::Auth()
    {
    }
    
    Auth::Auth(int id, int pth, const std::string& usr, const std::string& pass):
    Model::BaseModel(id),
    path_id(pth),
    username(usr),
    password(pass)
    {
        
    }
    
    Auth::Auth(int pth, const std::string& user, const std::string& pass):
        path_id(pth),
        username(user),
        password(pass)
    {
        
    }
    
    Auth::Auth(int pth):
        path_id(pth)
    {
        
    }
    
    Auth::~Auth()
    {
        
    }
    
    void Auth::setPathId(int pth)
    {
        path_id = pth;
    }
    
    void Auth::setUsername(const std::string &usr)
    {
        username = usr;
    }
    
    void Auth::setPassword(const std::string &pass)
    {
        password = pass;
    }
    
    int Auth::getPathId() const noexcept
    {
        return path_id;
    }
    
    const std::string Auth::getPassword() const noexcept {
        return password;
    }
    
    const std::string Auth::getUsername() const noexcept {
        return username;
    }
    
}


