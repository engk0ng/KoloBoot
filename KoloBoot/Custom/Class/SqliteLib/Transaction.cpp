//
//  Transaction.cpp
//  KoloBoot
//
//  Created by Abu Muhammad on 09/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#include "Transaction.h"

#include "Database.h"
#include "Assertion.h"

namespace SQLite {
    Transaction::Transaction(Database& aDatabase):
        mDatabase(aDatabase),
        mbCommited(false)
    {
        mDatabase.exec("BEGIN");
    }
    
    Transaction::~Transaction()
    {
        if (false == mbCommited) {
            try {
                mDatabase.exec("ROLLBACK");
            } catch (SQLite::Exception&) {
                
            }
        }
    }
    
    void Transaction::commit()
    {
        if (false == mbCommited) {
            mDatabase.exec("COMMIT");
            mbCommited = true;
        }
        else
        {
            throw SQLite::Exception("Transaction already commited.");
        }
    }
}
