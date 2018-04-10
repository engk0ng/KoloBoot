//
//  Project.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef Project_hpp
#define Project_hpp

#include <stdio.h>
#include "BaseModel.hpp"
#include <iostream>

namespace Model {
    class Project : public Model::BaseModel {
    public:
        Project(int, const std::string&, const std::string&);
        Project(const std::string&, const std::string&);
        Project();
        ~Project();
        void setBaseUrl(const std::string&);
        const std::string getBaseUrl() const noexcept;
        
        std::ostream& operator<<(std::ostream& os);
        
    private:
        std::string base_url;
    };
}

#endif /* Project_hpp */
