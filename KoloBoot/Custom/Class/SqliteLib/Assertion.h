/**
 * @file    Assertion.h
 * @ingroup SQLiteCpp
 * @brief   Definition of the SQLITECPP_ASSERT() macro.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <stdio.h>
#include <cassert>

#ifdef SQLITECPP_ENABLE_ASSERT_HANDLER

namespace SQLite {
    void assertion_failed(const char *apFile, const long apLine, const char *apFunc,
                          const char *apExpr, const char *apMsg);
    #define SQLITECPP_ASSERT(expression, message) \
        if (!(expression))  SQLite::assertion_failed(__FILE__, __LINE__, __func__, #expression, message)
}

#else
    #define SQLITECPP_ASSERT(expression, message)   assert(expression && message)
#endif /* Assertion_h */
