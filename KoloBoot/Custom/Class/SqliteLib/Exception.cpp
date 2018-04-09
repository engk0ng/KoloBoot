/**
 * @file    Exception.cpp
 * @ingroup SQLiteCpp
 * @brief   Encapsulation of the error message from SQLite3 on a std::runtime_error.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Exception.h"
#include <sqlite3.h>

namespace SQLite {
    Exception::Exception(const char *aErrorMessage):
        std::runtime_error(aErrorMessage),
        mErrorCode(-1),
        mExtendedErrorCode(-1)
    {
    }
    
    Exception::Exception(const std::string& aErrorMessage):
        std::runtime_error(aErrorMessage),
        mErrorCode(-1),
        mExtendedErrorCode(-1)
    {
    }
    
    Exception::Exception(const char *aErrorMessage, int ret):
        std::runtime_error(aErrorMessage),
        mErrorCode(ret),
        mExtendedErrorCode(-1)
    {
    }
    
    Exception::Exception(const std::string& aErrorMessage, int ret):
        std::runtime_error(aErrorMessage),
        mErrorCode(ret),
        mExtendedErrorCode(-1)
    {
    }
    
    Exception::Exception(sqlite3 *apSQLite):
        std::runtime_error(sqlite3_errmsg(apSQLite)),
        mErrorCode(sqlite3_errcode(apSQLite)),
        mExtendedErrorCode(sqlite3_extended_errcode(apSQLite))
    {
    }
    
    Exception::Exception(sqlite3 *apSqlite, int ret):
        std::runtime_error(sqlite3_errmsg(apSqlite)),
        mErrorCode(ret),
        mExtendedErrorCode(sqlite3_extended_errcode(apSqlite))
    {
    }
    
    const char *Exception::getErrorStr() const noexcept {
        return sqlite3_errstr(mErrorCode);
    }
}
