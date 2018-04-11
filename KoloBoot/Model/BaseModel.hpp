//
//  BaseModel.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef BaseModel_hpp
#define BaseModel_hpp

#include <stdio.h>
#include <string>

namespace Model {
    class BaseModel {
    public:
        BaseModel(int, const std::string&);
        BaseModel(const std::string&);
        BaseModel(int);
        BaseModel();
        virtual ~BaseModel();
        virtual void setName(const std::string&);
        virtual void setId(int);
        virtual const std::string getName() const noexcept;
        virtual int getId() const noexcept;
        
    private:
        std::string name;
        int _id;
    };
}

#endif /* BaseModel_hpp */
