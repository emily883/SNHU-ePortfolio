// =============================================================
//  Student Portal — AuthService.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     implement seed of default users and the login check.
// =============================================================
#include "AuthService.h"
#include <iostream>

AuthService::AuthService(IUserRepository& users, PasswordHasher& hasher)
    : users(users), hasher(hasher) {
}

// if there is no users yet (first time the program run) i make two: admin
// can write, user only read. i hash the password with a fresh salt before
// saving, so the database never see the real password
void AuthService::seedDefaultUsersIfEmpty() {
    if (users.count() > 0) {
        return;
    }

    std::string adminSalt = hasher.generateSalt();
    users.addUser("admin", hasher.hash("admin123", adminSalt), adminSalt, Role::Admin);

    std::string userSalt = hasher.generateSalt();
    users.addUser("user", hasher.hash("user123", userSalt), userSalt, Role::User);

    std::cout << "(first run) i made two default users:\n"
              << "   admin / admin123  -> can add, update, delete\n"
              << "   user  / user123   -> can only read\n";
}

// the login: i read the saved hash + salt for that username, i hash the
// password the person type with the SAME salt, and i compare. if equal the
// password is correct. if the user no exist i just say no
std::optional<User> AuthService::login(const std::string& username,
                                       const std::string& password) const {
    std::string savedHash;
    std::string salt;
    if (!users.getCredentials(username, savedHash, salt)) {
        return std::nullopt;   // no such user
    }

    std::string tryHash = hasher.hash(password, salt);
    if (tryHash == savedHash) {
        return users.findByUsername(username);   // give back name + role
    }
    return std::nullopt;   // wrong password
}
/* emily cruz check the login here :) */
