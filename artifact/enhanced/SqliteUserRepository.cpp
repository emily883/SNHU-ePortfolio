// =============================================================
//  Student Portal — SqliteUserRepository.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     SQLite implementation of the user storage. every query is
//              a prepared statement (bind the values, never glue strings).
// =============================================================
#include "SqliteUserRepository.h"

#include <stdexcept>
#include <iostream>

// open the file and make the table if is not there yet. i throw if the db
// can not open because without it the login can not work
SqliteUserRepository::SqliteUserRepository(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("can not open user database");
    }
    const char* ddl =
        "CREATE TABLE IF NOT EXISTS users ("
        " username TEXT PRIMARY KEY,"
        " password_hash TEXT NOT NULL,"
        " salt TEXT NOT NULL,"
        " role TEXT NOT NULL);";
    char* err = nullptr;
    if (sqlite3_exec(db, ddl, nullptr, nullptr, &err) != SQLITE_OK) {
        std::string msg = err ? err : "unknown";
        sqlite3_free(err);
        throw std::runtime_error("can not create users table: " + msg);
    }
}

SqliteUserRepository::~SqliteUserRepository() {
    sqlite3_close(db);   // always close so we no leak the connection
}

// i bind the values with ? marks, this is the parameterized way. if i glue
// the username inside the sql string somebody could put ' OR 1=1 and break
// the login, but with bind that is just text, no danger
void SqliteUserRepository::addUser(const std::string& username,
                                   const std::string& passwordHash,
                                   const std::string& salt,
                                   Role role) {
    const char* sql =
        "INSERT INTO users (username, password_hash, salt, role) "
        "VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }
    std::string roleText = roleToString(role);
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, passwordHash.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, salt.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, roleText.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::optional<User> SqliteUserRepository::findByUsername(const std::string& username) const {
    const char* sql = "SELECT username, role FROM users WHERE username = ?;";
    sqlite3_stmt* stmt = nullptr;
    std::optional<User> result;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* name = sqlite3_column_text(stmt, 0);
            const unsigned char* role = sqlite3_column_text(stmt, 1);
            result = User(name ? reinterpret_cast<const char*>(name) : "",
                          roleFromString(role ? reinterpret_cast<const char*>(role) : "user"));
        }
    }
    sqlite3_finalize(stmt);
    return result;
}

bool SqliteUserRepository::getCredentials(const std::string& username,
                                          std::string& outHash,
                                          std::string& outSalt) const {
    const char* sql = "SELECT password_hash, salt FROM users WHERE username = ?;";
    sqlite3_stmt* stmt = nullptr;
    bool found = false;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char* h = sqlite3_column_text(stmt, 0);
            const unsigned char* s = sqlite3_column_text(stmt, 1);
            outHash = h ? reinterpret_cast<const char*>(h) : "";
            outSalt = s ? reinterpret_cast<const char*>(s) : "";
            found = true;
        }
    }
    sqlite3_finalize(stmt);
    return found;
}

int SqliteUserRepository::count() const {
    const char* sql = "SELECT COUNT(*) FROM users;";
    sqlite3_stmt* stmt = nullptr;
    int n = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            n = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return n;
}
/* emily cruz was here :) */
