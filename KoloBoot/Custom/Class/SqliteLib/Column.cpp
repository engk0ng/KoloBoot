/**
 * @file    Column.h
 * @ingroup SQLiteCpp
 * @brief   Encapsulation of a Column in a row of the result pointed by the prepared SQLite::Statement.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Column.h"
#include <sqlite3.h>
#include <iostream>

namespace SQLite {
    const int INTEGER = SQLITE_INTEGER;
    const int FLOAT = SQLITE_FLOAT;
    const int TEXT = SQLITE_TEXT;
    const int BLOB = SQLITE_BLOB;
    const int Null = SQLITE_NULL;
    
    Column::Column(Statement::Ptr& aSmtPtr, int aIndex) noexcept:
        mStmtPtr(aSmtPtr),
        mIndex(aIndex)
    {
    }
    
    Column::~Column() {}
    
    const char *Column::getName() const noexcept {
        return sqlite3_column_name(mStmtPtr, mIndex);
    }
#ifdef SQLITE_ENABLE_COLUMN_METADATA
    const char *Column::getOriginName() const noexcept {
        return sqlite3_column_origin_name(mStmtPtr, mIndex);
    }
#endif
    int Column::getInt() const noexcept {
        return sqlite3_column_int(mStmtPtr, mIndex);
    }
    
    unsigned Column::getUInt() const noexcept {
        return  static_cast<unsigned>(getInt64());
    }
    
    long long Column::getInt64() const noexcept {
        return sqlite3_column_int64(mStmtPtr, mIndex);
    }
    
    double Column::getDouble() const noexcept {
        return sqlite3_column_double(mStmtPtr, mIndex);
    }
    
    const char *Column::getText(const char *apDefaultValue /* = "" */) const noexcept {
        const char *pText = reinterpret_cast<const char *>(sqlite3_column_text(mStmtPtr, mIndex));
        return (pText?pText:apDefaultValue);
    }
    
    const void *Column::getBlob() const noexcept {
        return sqlite3_column_blob(mStmtPtr, mIndex);
    }
    
    std::string Column::getString() const {
        const char *data = static_cast<const char *>(sqlite3_column_blob(mStmtPtr, mIndex));
        return std::string(data, sqlite3_column_bytes(mStmtPtr, mIndex));
    }
    
    int Column::getType() const noexcept {
        return sqlite3_column_type(mStmtPtr, mIndex);
    }
    
    int Column::getBytes() const noexcept {
        return sqlite3_column_bytes(mStmtPtr, mIndex);
    }
    
    std::ostream& operator<<(std::ostream& aStream, const Column& aColumn) {
        aStream.write(aColumn.getText(), aColumn.getBytes());
        return aStream;
    }
}
