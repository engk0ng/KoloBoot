/**
 * @file    Database.cpp
 * @ingroup SQLiteCpp
 * @brief   Management of a SQLite Database Connection.
 *
 * Copyright (c) 2012-2018 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include "Database.h"

#include "Statement.h"
#include "Assertion.h"
#include "Exception.h"

#include <sqlite3.h>
#include <fstream>
#include <string.h>

#ifndef SQLITE_DETERMINISTIC
#define SQLITE_DETERMINISTIC 0x800
#endif // SQLITE_DETERMINISTIC


namespace SQLite {
    const int   OPEN_READONLY   = SQLITE_OPEN_READONLY;
    const int   OPEN_READWRITE  = SQLITE_OPEN_READWRITE;
    const int   OPEN_CREATE     = SQLITE_OPEN_CREATE;
    const int   OPEN_URI        = SQLITE_OPEN_URI;
    
    const int   OK              = SQLITE_OK;
    
    const char* VERSION         = SQLITE_VERSION;
    const int   VERSION_NUMBER  = SQLITE_VERSION_NUMBER;
    
    const char* getLibVersion() noexcept // nothrow
    {
        return sqlite3_libversion();
    }
    
    int getLibVersionNumber() noexcept // nothrow
    {
        return sqlite3_libversion_number();
    }
    
    Database::Database(const char* apFilename,
                       const int   aFlags         /* = SQLite::OPEN_READONLY*/,
                       const int   aBusyTimeoutMs /* = 0 */,
                       const char* apVfs          /* = nullptr*/) :
    mpSQLite(nullptr),
    mFilename(apFilename)
    {
        const int ret = sqlite3_open_v2(apFilename, &mpSQLite, aFlags, apVfs);
        if (SQLITE_OK != ret) {
            const SQLite::Exception exception(mpSQLite, ret);
            sqlite3_close(mpSQLite);
            throw exception;
        }
        if (aBusyTimeoutMs > 0) {
            setBusyTimeout(aBusyTimeoutMs);
        }
    }
    
    Database::Database(const std::string& aFilename,
                       const int          aFlags         /* = SQLite::OPEN_READONLY*/,
                       const int          aBusyTimeoutMs /* = 0 */,
                       const std::string& aVfs           /* = "" */) :
    mpSQLite(nullptr),
    mFilename(aFilename)
    {
        const int ret = sqlite3_open_v2(aFilename.c_str(), &mpSQLite, aFlags, aVfs.empty() ? nullptr : aVfs.c_str());
        if (SQLITE_OK != ret) {
            const SQLite::Exception exception(mpSQLite, ret);
            sqlite3_close(mpSQLite);
            throw exception;
        }
        if (aBusyTimeoutMs > 0) {
            setBusyTimeout(aBusyTimeoutMs);
        }
    }
    
    Database::~Database() {
        const int ret = sqlite3_close(mpSQLite);
        (void) ret;
        
        SQLITECPP_ASSERT(SQLITE_OK == ret, "database is locked");
    }
    
    void Database::setBusyTimeout(const int aBusyTimeoutMs) {
        const int ret = sqlite3_busy_timeout(mpSQLite, aBusyTimeoutMs);
        check(ret);
    }
    
    int Database::exec(const char *apQueries) {
        const int ret = sqlite3_exec(mpSQLite, apQueries, nullptr, nullptr, nullptr);
        check(ret);
        return sqlite3_changes(mpSQLite);
    }
    
    Column Database::execAndGet(const char *apQuery) {
        Statement query(*this, apQuery);
        (void)query.executeStep();
        return query.getColumn(0);
    }
    
    bool Database::tableExists(const char *apTableName) {
        Statement query(*this, "SELECT count(*) FROM sqlite_master WHERE type = 'table' AND name = ?");
        query.bind(1, apTableName);
        (void)query.executeStep();
        return (1 == query.getColumn(0).getInt());
    }
    
    long long Database::getLastInsertRowid() const noexcept {
        return sqlite3_last_insert_rowid(mpSQLite);
    }
    
    int Database::getTotalChanges() const noexcept {
        return sqlite3_total_changes(mpSQLite);
    }
    
    int Database::getErrorCode() const noexcept {
        return sqlite3_extended_errcode(mpSQLite);
    }
    
    const char *Database::getErrorMsg() const noexcept {
        return sqlite3_errmsg(mpSQLite);
    }
    
    void Database::createFunction(const char*   apFuncName,
                                  int           aNbArg,
                                  bool          abDeterministic,
                                  void*         apApp,
                                  void        (*apFunc)(sqlite3_context *, int, sqlite3_value **),
                                  void        (*apStep)(sqlite3_context *, int, sqlite3_value **),
                                  void        (*apFinal)(sqlite3_context *),   // NOLINT(readability/casting)
                                  void        (*apDestroy)(void *))
    {
        int TextRep = SQLITE_UTF8;
        // optimization if deterministic function (e.g. of nondeterministic function random())
        if (abDeterministic) {
            TextRep = TextRep|SQLITE_DETERMINISTIC;
        }
        const int ret = sqlite3_create_function_v2(mpSQLite, apFuncName, aNbArg, TextRep,
                                                   apApp, apFunc, apStep, apFinal, apDestroy);
        check(ret);
    }
    
    void Database::key(const std::string &aKey) const {
        int pass_len = static_cast<int>(aKey.length());
#ifdef SQLITE_HAS_CODEC
        if (pass_len > 0) {
            const int ret = sqlite3_key(mpSQLite, aKey.c_str(), pass_len);
            check(ret);
        }
#else
        if (pass_len > 0) {
            const SQLite::Exception exception("No encryption support, recompile with SQLITE_HAS_CODEC to enable.");
            throw exception;
        }
#endif
    }
    
    // Reset the key for the current sqlite database instance.
    void Database::rekey(const std::string& aNewKey) const
    {
#ifdef SQLITE_HAS_CODEC
        int pass_len = aNewKey.length();
        if (pass_len > 0) {
            const int ret = sqlite3_rekey(mpSQLite, aNewKey.c_str(), pass_len);
            check(ret);
        } else {
            const int ret = sqlite3_rekey(mpSQLite, nullptr, 0);
            check(ret);
        }
#else // SQLITE_HAS_CODEC
        static_cast<void>(aNewKey); // silence unused parameter warning
        const SQLite::Exception exception("No encryption support, recompile with SQLITE_HAS_CODEC to enable.");
        throw exception;
#endif // SQLITE_HAS_CODEC
    }
    
    // Test if a file contains an unencrypted database.
    bool Database::isUnencrypted(const std::string& aFilename)
    {
        if (aFilename.length() > 0) {
            std::ifstream fileBuffer(aFilename.c_str(), std::ios::in | std::ios::binary);
            char header[16];
            if (fileBuffer.is_open()) {
                fileBuffer.seekg(0, std::ios::beg);
                fileBuffer.getline(header, 16);
                fileBuffer.close();
            } else {
                const SQLite::Exception exception("Error opening file: " + aFilename);
                throw exception;
            }
            return strncmp(header, "SQLite format 3\000", 16) == 0;
        }
        const SQLite::Exception exception("Could not open database, the aFilename parameter was empty.");
        throw exception;
    }
}
