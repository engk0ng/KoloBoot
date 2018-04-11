//
//  Param.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "Param.hpp"

namespace Model {
    Param::Param()
    {
        
    }
    
    Param::Param(int id, int pat, const std::string& ky, const std::string& val, int tp):
        Model::BaseModel(id),
        Model::GeneralModel(tp),
        path_id(pat),
        key(ky),
        value(val)
    {
        
    }
    
    Param::Param(int pat, const std::string& ky, const std::string& val, int tp):
        Model::GeneralModel(tp),
        path_id(pat),
        key(ky),
        value(val)
    {
        
    }
    
    void Param::setPathId(int pat)
    {
        path_id = pat;
    }
    
    void Param::setKey(const std::string &ky)
    {
        key = ky;
    }
    
    void Param::setValue(const std::string &val)
    {
        value = val;
    }
    
    int Param::getPathId() const noexcept
    {
        return path_id;
    }
    
    const std::string Param::getKey() const noexcept
    {
        return key;
    }
    
    const std::string Param::getValue() const noexcept
    {
        return value;
    }
}
