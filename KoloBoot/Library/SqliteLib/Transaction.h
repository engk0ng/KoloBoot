/**
 * @file    Transaction.h
 * @ingroup SQLiteCpp
 * @brief   A Transaction is way to group multiple SQL statements into an atomic secured operation.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef Transaction_h
#define Transaction_h

#include <stdio.h>
#include "Exception.h"

namespace SQLite {
    class Database;
    
    class Transaction {
    public:
        explicit Transaction(Database& aDatabase);
        ~Transaction();
        
        void commit();
        
    private:
        Transaction(const Transaction&);
        Transaction& operator=(const Transaction&);
    private:
        Database& mDatabase;
        bool mbCommited;
    };
}

#endif /* Transaction_h */
