/**
 * @file    Database.h
 * @ingroup SQLiteCpp
 * @brief   Management of a SQLite Database Connection.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#ifndef Database_h
#define Database_h

#include <stdio.h>
#include "Column.h"
#include "Utils.h"
#include <string>

struct sqlite3;
struct sqlite3_context;

#ifndef SQLITE_USE_LEGACY_STRUCT // Since SQLITE 3.19 (used by default since SQLiteCpp 2.1.0)
typedef struct sqlite3_value sqlite3_value;
#else // Before SQLite 3.19 (legacy struct forward declaration can be activated with CMake SQLITECPP_LEGACY_STRUCT var)
struct Mem;
typedef struct Mem sqlite3_value;
#endif

namespace SQLite {
    extern const int OPEN_READONLY;
    extern const int OPEN_READWRITE;
    extern const int OPEN_CREATE;
    extern const int OPEN_URI;
    extern const int OK;
    extern const char *VERSION;
    extern const int VERSION_NUMBER;
    
    const char *getLibVersion() noexcept;
    int getLibVersionNumber() noexcept;
    
    class Database {
        friend class Statement;
        
    public:
        Database(const char* apFilename,
                 const int   aFlags         = SQLite::OPEN_READONLY,
                 const int   aBusyTimeoutMs = 0,
                 const char* apVfs          = nullptr);
        
        Database(const std::string& aFilename,
                 const int          aFlags          = SQLite::OPEN_READONLY,
                 const int          aBusyTimeoutMs  = 0,
                 const std::string& aVfs            = "");
        
        ~Database();
        
        void setBusyTimeout(const int aBusyTimeoutMs);
        
        int exec(const char* apQueries);
        
        inline int exec(const std::string& aQueries)
        {
            return exec(aQueries.c_str());
        }
        
        Column execAndGet(const char* apQuery);
        
        inline Column execAndGet(const std::string& aQuery)
        {
            return execAndGet(aQuery.c_str());
        }
        
        bool tableExists(const char* apTableName);
        
        inline bool tableExists(const std::string& aTableName)
        {
            return tableExists(aTableName.c_str());
        }
        
        long long getLastInsertRowid() const noexcept;
        int getTotalChanges() const noexcept;
        int getErrorCode() const noexcept;
        int getExtendedErrorCode() const noexcept;
        const char* getErrorMsg() const noexcept;
        const std::string& getFilename() const noexcept // nothrow
        {
            return mFilename;
        }
        
        inline sqlite3* getHandle() const noexcept // nothrow
        {
            return mpSQLite;
        }
        
        void createFunction(const char* apFuncName,
                            int         aNbArg,
                            bool        abDeterministic,
                            void*       apApp,
                            void      (*apFunc)(sqlite3_context *, int, sqlite3_value **),
                            void      (*apStep)(sqlite3_context *, int, sqlite3_value **),
                            void      (*apFinal)(sqlite3_context *),  // NOLINT(readability/casting)
                            void      (*apDestroy)(void *));
        
        inline void createFunction(const std::string&   aFuncName,
                                   int                  aNbArg,
                                   bool                 abDeterministic,
                                   void*                apApp,
                                   void               (*apFunc)(sqlite3_context *, int, sqlite3_value **),
                                   void               (*apStep)(sqlite3_context *, int, sqlite3_value **),
                                   void               (*apFinal)(sqlite3_context *), // NOLINT(readability/casting)
                                   void               (*apDestroy)(void *))
        {
            return createFunction(aFuncName.c_str(), aNbArg, abDeterministic,
                                  apApp, apFunc, apStep, apFinal, apDestroy);
        }
        
        //void loadExtension(const char* apExtensionName, const char* apEntryPointName);
        
        void key(const std::string& aKey) const;
        
        void rekey(const std::string& aNewKey) const;
        
        static bool isUnencrypted(const std::string& aFilename);
        
    private:
        Database(const Database&);
        Database& operator=(const Database&);
        
        inline void check(const int aRet) const
        {
            if (SQLite::OK != aRet)
            {
                throw SQLite::Exception(mpSQLite, aRet);
            }
        }
        
    private:
        sqlite3*    mpSQLite;   ///< Pointer to SQLite Database Connection Handle
        std::string mFilename;  ///< UTF-8 filename used to open the database
    };
}

#endif /* Database_h */
