//
//  Auth.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 13/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef Auth_hpp
#define Auth_hpp

#include <stdio.h>
#include "BaseModel.hpp"

namespace Model {
    class Auth: public Model::BaseModel
    {
    public:
        Auth();
        Auth(int, int, const std::string&, const std::string&);
        Auth(int, const std::string&, const std::string&);
        Auth(int);
        ~Auth();
        void setUsername(const std::string&);
        void setPassword(const std::string&);
        const std::string getUsername() const noexcept;
        const std::string getPassword() const noexcept;
        void setPathId(int);
        int getPathId() const noexcept;
    private:
        std::string username;
        std::string password;
        int path_id;
    };
}

#endif /* Auth_hpp */
