// =============================================================
//  Student Portal — PasswordHasher.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     hash passwords with a salt so i never save the real
//              password. uses SHA-256 from OpenSSL.
// =============================================================
#ifndef PASSWORD_HASHER_H
#define PASSWORD_HASHER_H

#include <string>

// i never store the password like the person type it. i make a random
// salt and i save SHA-256(salt + password). when somebody login i do the
// same math and compare the hash. (note: bcrypt/argon2 would be better
// for real production, but for this course sha256 + salt show the idea)
class PasswordHasher {
public:
    // give a new random salt (hex string), different for each user
    std::string generateSalt() const;

    // return SHA-256 of (salt + password) as a hex string
    std::string hash(const std::string& password, const std::string& salt) const;
};

#endif
/* emily cruz hash the password here :) */
