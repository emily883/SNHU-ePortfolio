// =============================================================
//  Student Portal — SqliteUserRepository.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     store the users in a SQLite table, with prepared
//              statements so nobody can do SQL injection on the login.
// =============================================================
#ifndef SQLITE_USER_REPOSITORY_H
#define SQLITE_USER_REPOSITORY_H

#include "UserRepository.h"
#include <sqlite3.h>

// the users live in the table "users" inside the same sqlite file. i keep
// username, the password hash, the salt and the role
class SqliteUserRepository : public IUserRepository {
private:
    sqlite3* db = nullptr;

public:
    explicit SqliteUserRepository(const std::string& dbPath);
    ~SqliteUserRepository() override;

    void addUser(const std::string& username,
                 const std::string& passwordHash,
                 const std::string& salt,
                 Role role) override;
    std::optional<User> findByUsername(const std::string& username) const override;
    bool getCredentials(const std::string& username,
                        std::string& outHash,
                        std::string& outSalt) const override;
    int count() const override;
};

#endif
/* emily cruz was here :) */
