//
//  BaseModel.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "BaseModel.hpp"

namespace Model {
    BaseModel::BaseModel() {}
    
    BaseModel::BaseModel(int id, const std::string& nm):
        _id(id), name(nm)
    {
    }
    
    BaseModel::BaseModel(const std::string& nm):
        name(nm)
    {
    }
    
    BaseModel::~BaseModel() {}
    
    void BaseModel::setId(int id)
    {
        _id = id;
    }
    
    void BaseModel::setName(const std::string &nm)
    {
        name = nm;
    }
    
    const std::string BaseModel::getName() const noexcept
    {
        return name;
    }
    
    int BaseModel::getId() const noexcept
    {
        return _id;
    }
}




