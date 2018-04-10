/**
 * @file    Exception.h
 * @ingroup SQLiteCpp
 * @brief   Encapsulation of the error message from SQLite3 on a std::runtime_error.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef Exception_h
#define Exception_h

#include <stdio.h>
#include <stdexcept>
#include <string>

struct sqlite3;

namespace SQLite {
    class Exception: public std::runtime_error {
    public:
        explicit Exception(const char *aErrorMessage);
        explicit Exception(const std::string& aErrorMessage);
        
        Exception(const char *aErrorMessage, int ret);
        Exception(const std::string& aErrorMessage, int ret);
        
        explicit Exception(sqlite3 *apSqlite);
        
        Exception(sqlite3 *apSqlite, int ret);
        
        inline int getErrorCode() const noexcept {
            return mErrorCode;
        }
        
        inline int getExtendedErrorCode() const noexcept {
            return mExtendedErrorCode;
        }
        
        const char* getErrorStr() const noexcept;
    private:
        int mErrorCode;
        int mExtendedErrorCode;
    };
}

#endif /* Exception_h */
