// =============================================================
//  Student Portal — User.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     small model for a logged-in user (username + role).
//              used by the login and the access levels (admin vs user).
// =============================================================
#ifndef USER_H
#define USER_H

#include <string>

// only two kind of user for now. admin can write (add/update/delete),
// the normal user can only read. least privilege: if i no know, is user
enum class Role { User, Admin };

// little helpers to turn the role into text and back, because in the
// database i save the role as a word ("admin"/"user")
inline std::string roleToString(Role r) {
    return r == Role::Admin ? "admin" : "user";
}
inline Role roleFromString(const std::string& s) {
    return s == "admin" ? Role::Admin : Role::User;
}

// the user is just who is logged in. i no keep the password here, only
// the name and what they are allow to do
class User {
private:
    std::string username;
    Role role;

public:
    User(std::string username, Role role)
        : username(std::move(username)), role(role) {}

    std::string getUsername() const { return username; }
    Role getRole() const { return role; }
    bool isAdmin() const { return role == Role::Admin; }
};

#endif
/* emily cruz was here :) */
