//
//  Column.hpp
//  KoloBoot
//
//  Created by Abu Muhammad on 08/04/18.
//  Copyright © 2018 Abu Muhammad. All rights reserved.
//

#ifndef Column_h
#define Column_h

#include <stdio.h>
#include "Statement.h"
#include "Exception.h"

#include <string>
#include <climits>

namespace SQLite {
    extern const int INTEGER;
    extern const int FLOAT;
    extern const int TEXT;
    extern const int BLOB;
    extern const int Null;
    
    class Column {
    public:
        Column(Statement::Ptr& aStmtPtr, int aIndex) noexcept;
        ~Column();
        
        Column(const Column &aOther):
            mStmtPtr(aOther.mStmtPtr),
            mIndex(aOther.mIndex)
        {
        }
        
        const char *getName() const noexcept;
        
#ifdef SQLITE_ENABLE_COLUMN_METADATA
        const char *getOriginName() const noexcept;
#endif
        int getInt() const noexcept;
        unsigned getUInt() const noexcept;
        long long getInt64() const noexcept;
        double getDouble() const noexcept;
        
        const char *getText(const char *apDefaultValue = "") const noexcept;
        
        const void *getBlob() const noexcept;
        
        std::string getString() const;
        
        int getType() const noexcept;
        
        inline bool isInteger() const noexcept {
            return (SQLite::INTEGER == getType());
        }
        
        inline bool isFloat() const noexcept {
            return (SQLite::FLOAT == getType());
        }
        
        inline bool isText() const noexcept {
            return (SQLite::TEXT == getType());
        }
        
        inline bool isBlob() const noexcept {
            return (SQLite::BLOB == getType());
        }
        
        inline bool isNull() const noexcept {
            return (SQLite::Null == getType());
        }
        
        int getBytes() const noexcept;
        
        inline int size() const noexcept {
            return  getBytes();
        }
        
        inline operator int() const {
            return getInt();
        }
        
        inline operator unsigned int() const {
            return getUInt();
        }
        
#if (LONG_MAX == INT_MAX)
        
        inline operator long() const {
            return getInt();
        }
        
        inline operator unsigned long() const {
            return getUInt();
        }
        
#else
        inline operator long() const {
            return getInt64();
        }
        
#endif
        inline operator long long() const {
            return  getInt64();
        }
        
        inline operator double() const {
            return getDouble();
        }
        
        inline operator const char *() const {
            return getText();
        }
        
        inline operator const void *() const {
            return getBlob();
        }
#if !(defined(_MSC_VER) && _MSC_VER < 1900)
        inline operator std::string() const
        {
            return getString();
        }
#endif
        
        
    private:
        Statement::Ptr mStmtPtr;
        int mIndex;
    };
    
    std::ostream& operator<<(std::ostream& aStream, const Column& aColumn);
    
#if __cplusplus >= 201402L || (defined(_MSC_VER) && _MSC_VER >= 1900)
    template<typename T, int N>
    T Statement::getColumns() {
        checkRow();
        checkIndex(N - 1);
        return getColumns<T>(std::make_integer_sequence<int, N>{});
    }
    
    template<typename T, const int... Is>
    T Statement::getColumns(const std::integer_sequence<int, Is...>) {
        return T{Column(mStmtPtr, Is)...};
    }
#endif
    
}

#endif /* Column_h */
