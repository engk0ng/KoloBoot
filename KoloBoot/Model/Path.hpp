//
//  Path.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <stdio.h>
#include "BaseModel.hpp"
#include "GeneralModel.hpp"

namespace Model {
    class Path : public Model::BaseModel, public Model::GeneralModel {
    public:
        Path(int, int, const std::string&, const std::string&, std::string&&);
        Path(int, const std::string&, const std::string&, std::string&&);
        Path();
        ~Path();
        void setProjectId(int);
        int getProjectId() const noexcept;
        
        void setPath(const std::string&);
        const std::string getPath() const noexcept;
        
    private:
        int project_id;
        std::string path;
    };
}
#endif /* Path_hpp */
