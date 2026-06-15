// =============================================================
//  Student Portal — UserRepository.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     interface (contract) for where the users are stored.
//              same repository pattern idea as the students.
// =============================================================
#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include <string>
#include <optional>
#include "User.h"

// the contract for the user storage. the auth service only talk to this,
// it no care if the users live in sqlite or somewhere else
class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    // save a new user with the already hashed password and the salt
    virtual void addUser(const std::string& username,
                         const std::string& passwordHash,
                         const std::string& salt,
                         Role role) = 0;

    // get the user (name + role) if exist, for after the login is ok
    virtual std::optional<User> findByUsername(const std::string& username) const = 0;

    // get the saved hash and salt so the auth service can compare. return
    // false if the user no exist
    virtual bool getCredentials(const std::string& username,
                               std::string& outHash,
                               std::string& outSalt) const = 0;

    // how many users, so on first run i know i must seed the defaults
    virtual int count() const = 0;
};

#endif
/* emily cruz was here too :) */
