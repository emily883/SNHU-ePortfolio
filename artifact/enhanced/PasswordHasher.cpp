// =============================================================
//  Student Portal — PasswordHasher.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     implement the salt + SHA-256 hashing using OpenSSL EVP.
// =============================================================
#include "PasswordHasher.h"

#include <openssl/evp.h>
#include <random>
#include <sstream>
#include <iomanip>

// turn bytes into a hex string, so i can save it as text in the database
static std::string toHex(const unsigned char* data, unsigned int len) {
    std::ostringstream oss;
    for (unsigned int i = 0; i < len; ++i) {
        oss << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(data[i]);
    }
    return oss.str();
}

// random salt: i make 16 random bytes and put them in hex. random_device
// give me numbers from the system, good enough for a salt
std::string PasswordHasher::generateSalt() const {
    std::random_device rd;
    unsigned char bytes[16];
    for (unsigned char& b : bytes) {
        b = static_cast<unsigned char>(rd() & 0xFF);
    }
    return toHex(bytes, 16);
}

// here is the real hashing with OpenSSL. i use the EVP api (the new one,
// the old SHA256() give deprecation warning). i hash salt+password so two
// people with same password still get different hash
std::string PasswordHasher::hash(const std::string& password,
                                 const std::string& salt) const {
    std::string input = salt + password;

    unsigned char out[EVP_MAX_MD_SIZE];
    unsigned int outLen = 0;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx, input.data(), input.size());
    EVP_DigestFinal_ex(ctx, out, &outLen);
    EVP_MD_CTX_free(ctx);

    return toHex(out, outLen);
}
/* emily cruz hash the password here :) */
