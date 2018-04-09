/**
 * @file    Statement.h
 * @ingroup SQLiteCpp
 * @brief   A prepared SQLite Statement is a compiled SQL query ready to be executed, pointing to a row of result.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef Statement_h
#define Statement_h

#include <stdio.h>
#include "Exception.h"

#include <string>
#include <map>
#include <climits>

struct sqlite3;
struct sqlite3_stmt;

namespace SQLite {
    class Database;
    class Column;
    
    extern const int OK;
    
    class Statement {
        friend class Column;
    public:
        Statement(Database& aDatabase, const char *apQuery);
        Statement(Database& aDatabase, const std::string& qQuery);
        ~Statement();
        void reset();
        int tryReset() noexcept;
        void clearBindings();
        void bind(const int aIndex, const int aValue);
        void bind(const int aIndex, const unsigned aValue);
        
#if (LONG_MAX == INT_MAX)
        void bind(const int aIndex, const long aValue) {
            bind(aIndex, static_cast<int>(aValue));
        }
#else
        void bind(const int aIndex, const long aValue) {
            bind(aIndex, static_cast<long long>(aValue));
        }
#endif
        void bind(const int aIndex, const long long aValue);
        void bind(const int aIndex, const double aValue);
        void bind(const int aIndex, const std::string& aValue);
        void bind(const int aIndex, const char *apValue);
        void bind(const int aIndex, const void *apValue, const int aSize);
        void bindNoCopy(const int aIndex, const std::string& aValue);
        void bindNoCopy(const int aIndex, const char *apValue);
        void bindNoCopy(const int aIndex, const void *apValues, const int aSize);
        void bind(const int aIndex);
        void bind(const char *apName, const int aValue);
        void bind(const char *apName, const unsigned aValue);
#if (LONG_MAX == INT_MAX)
        void bind(const char *apName, const long aValue) {
            bind(apName, static_cast<int>(aValue));
        }
#else
        void bind(const char *apName, const long aValue) {
            bind(apName, static_cast<long long>(aValue));
        }
#endif
        void bind(const char *apName, const long long aValue);
        void bind(const char *apName, const double aValue);
        void bind(const char *apName, const std::string& aValue);
        
        void bind(const char *apName, const char *apValue);
        void bind(const char *apName, const char *apValue, const int aSize);
        void bind(const char* apName, const void *apValue, const int aSize);
        
        void bindNoCopy(const char *apName, const std::string& value);
        void bindNoCopy(const char *apName, const char *apValue);
        void bindNoCopy(const char *apName, const void *apValue, const int aSize);
        
        void bind(const char *apName);
        
        inline void bind(const std::string& aName, const int aValue) {
            bind(aName.c_str(), aValue);
        }
        
        inline void bind(const std::string& aName, const unsigned aValue) {
            bind(aName.c_str(), static_cast<int>(aValue));
        }
        
#if (LONG_MAX == INT_MAX)
        void bind(const std::string& aName, const long aValue) {
            bind(aName.c_str(), static_cast<int>(aValue));
        }
#else
        void bind(const std::string& aName, const long aValue) {
            bind(aName.c_str(), static_cast<long long>(aValue));
        }
#endif
        inline void bind(const std::string& aName, const long long aValue) {
            bind(aName.c_str(), aValue);
        }
        
        inline void bind(const std::string& aName, const double aValue) {
            bind(aName.c_str(), aValue);
        }
        
        inline void bind(const std::string& aName, const std::string& aValue) {
            bind(aName.c_str(), aValue);
        }
        
        inline void bind(const std::string& aName, const char *aValue) {
            bind(aName.c_str(), aValue);
        }
        
        inline void bind(const std::string& aName, const void *apValue, const int aSize) {
            bind(aName.c_str(), apValue, aSize);
        }
        
        inline void bindNoCopy(const std::string& aName, const std::string& aValue) {
            bindNoCopy(aName.c_str(), aValue);
        }
        
        inline void bindNoCopy(const std::string& aName, const char *apValue) {
            bindNoCopy(aName.c_str(), apValue);
        }
        
        inline void bindNoCopy(const std::string& aName, const void *apValue, const int aSize) {
            bindNoCopy(aName.c_str(), apValue, aSize);
        }
        
        inline void bind(const std::string& aName) {
            bind(aName.c_str());
        }
        
        bool executeStep();
        
        int tryExecuteStep() noexcept;
        
        int exec();
        
        Column getColumn(const int aIndex);
        
        Column getColumn(const char *apName);
        
#if __cplusplus >= 201402L || (defined(_MSC_VER) && _MSC_VER >= 1900)
        template <typename T, int N>
        T getColumns();
        
    private:
        template<typename T, const int... Is>
        T getColumns(const std::integer_sequence<int, Is...>);
    public:
#endif
        
        bool isColumnNull(const int aIndex) const;
        bool isColumnNull(const char *apName) const;
        const char *getColumnName(const int aIndex) const;
        
#ifdef SQLITE_ENABLE_COLUMN_METADATA
        const char *getColumnOriginName(const int aIndex) const;
#endif
        int getColumnIndex(const char *apName) const;
        
        inline const std::string& getQuery() const {
            return mQuery;
        }
        
        inline int getColumnCount() const {
            return mColumnCount;
        }
        
        inline bool hasRow() const {
            return mbHasRow;
        }
        
        inline bool isOk() const {
            return hasRow();
        }
        
        inline bool isDone() const {
            return mbDone;
        }
        
        int getErrorCode() const noexcept;
        int getExtendedErrorCode() const noexcept;
        const char *getErrorMsg() const noexcept;
        
    private:
        class Ptr {
        public:
            Ptr(sqlite3 *apSQLite, std::string& aQuery);
            Ptr(const Ptr& aPtr);
            ~Ptr();
            
            inline operator sqlite3*() const {
                return mpSQLite;
            }
            
            inline operator sqlite3_stmt*() const {
                return mpStmt;
            }
            
        private:
            Ptr& operator=(const Ptr& aPtr);
            
        private:
            sqlite3 *mpSQLite;
            sqlite3_stmt *mpStmt;
            unsigned int *mpRefCount;
        };
        
    private:
        Statement(const Statement&);
        Statement& operator=(const Statement&);
        
        inline void check(const int aRet) const {
            if (SQLite::OK != aRet) {
                throw SQLite::Exception(mStmtPtr, aRet);
            }
        }
        
        inline void checkRow() const {
            if (false == mbHasRow) {
                throw SQLite::Exception("No row to get a column from. executeStep() was not called, or returned false.");
            }
        }
        
        inline void checkIndex(const int aIndex) const {
            if ((aIndex < 0) || (aIndex >= mColumnCount))
            {
                throw SQLite::Exception("Column index out of range.");
            }
        }
    private:
        typedef std::map<std::string, int> TColumnNames;
    private:
        std::string mQuery;
        Ptr mStmtPtr;
        int mColumnCount;
        mutable TColumnNames mColumnNames;
        bool mbHasRow;
        bool mbDone;
    };
}

#endif /* Statement_h */
