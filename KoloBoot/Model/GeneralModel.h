//
//  GeneralModel.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 10/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef GeneralModel_h
#define GeneralModel_h

#include <stdio.h>
#include <type_traits>
#include <string>

namespace Model {
    template <typename T>
    using EnableString = std::enable_if_t<std::is_convertible<T, std::string>::value>;
    template <typename T>
    using EnableInteger = std::enable_if_t<std::is_same<int, T>::value>;
    
    class GeneralModel {
    public:
        GeneralModel()
        {
            
        }
        template <typename T, typename = EnableInteger<T>>
        GeneralModel(T t):type_int(t)
        {
            
        }
        template <typename T, typename = EnableString<T>>
        GeneralModel(T&& t):type_str(std::forward<T>(t))
        {
            
        }
        template <typename T, typename = EnableString<T>>
        void setType(T&& tp)
        {
            type_str = std::forward<T>(tp);
        }
        template <typename T, typename = EnableInteger<T>>
        void setType(T tp)
        {
            type_int = tp;
        }
        template <typename T, typename = EnableInteger<T>>
        T getType() const noexcept
        {
            return type_int;
        }
        
        template <typename T, typename = EnableString<T>>
        const T getType() const noexcept
        {
            return type_str;
        }
    private:
        std::string type_str;
        int type_int;
    };
}

#endif /* GeneralModel_h */
