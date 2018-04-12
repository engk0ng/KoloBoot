//
//  Param.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef Param_hpp
#define Param_hpp

#include <stdio.h>
#include "BaseModel.hpp"
#include "GeneralModel.h"

namespace Model {
    
    const int TYPE_QUERY = 1;
    const int TYPE_HEADER = 2;
    
    class Param: public Model::BaseModel, public Model::GeneralModel {
    public:
        Param();
        Param(int, int, const std::string&, const std::string&, int);
        Param(int, const std::string&, const std::string&, int);
        void setPathId(int);
        void setKey(const std::string&);
        void setValue(const std::string&);
        int getPathId() const noexcept;
        const std::string getKey() const noexcept;
        const std::string getValue() const noexcept;
    private:
        int path_id;
        std::string key;
        std::string value;
    };
}

#endif /* Param_hpp */
