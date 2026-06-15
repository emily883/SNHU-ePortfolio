// =============================================================
//  Student Portal — AuthService.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     handle the login. check the password against the hash and
//              tell who is the user (and the role).
// =============================================================
#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H

#include <optional>
#include <string>
#include "UserRepository.h"
#include "PasswordHasher.h"

// the auth service is the brain of the login. it use the user repository
// to read the saved hash, and the hasher to check the password the person
// type. it no know if the storage is sqlite, only the interface
class AuthService {
private:
    IUserRepository& users;
    PasswordHasher& hasher;

public:
    AuthService(IUserRepository& users, PasswordHasher& hasher);

    // on the very first run the table is empty, so i create two users so
    // the program is usable: an admin and a read-only user
    void seedDefaultUsersIfEmpty();

    // return the user if the password is correct, or nothing if not
    std::optional<User> login(const std::string& username,
                              const std::string& password) const;
};

#endif
/* emily cruz check the login here :) */
