// =============================================================
//  Student Portal — main.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     build all the layers, do the login, then run the portal.
//              this is the only place that pick the SQLite repos, so the
//              storage choice live in one spot.
// =============================================================
#include "SqliteStudentRepository.h"
#include "SqliteUserRepository.h"
#include "PasswordHasher.h"
#include "AuthService.h"
#include "StudentService.h"
#include "StudentController.h"

#include <iostream>
#include <optional>
#include <string>

int main() {
    // the database file. is a config value here, not glue inside the code.
    // both repos use the same file but different table
    const std::string dbPath = "students.db";

    SqliteStudentRepository studentRepo(dbPath);   // students live in sqlite now
    SqliteUserRepository userRepo(dbPath);         // users + roles also in sqlite
    PasswordHasher hasher;
    AuthService auth(userRepo, hasher);

    // first run make the default users so the program is usable
    auth.seedDefaultUsersIfEmpty();

    // login: i give the person a few tries. i read with getline so a name
    // with space no break it
    std::optional<User> user;
    std::cout << "\n=== Student Portal Login ===\n";
    for (int tries = 0; tries < 3 && !user.has_value(); ++tries) {
        std::string username, password;
        std::cout << "Username: ";
        std::getline(std::cin, username);
        std::cout << "Password: ";
        std::getline(std::cin, password);

        user = auth.login(username, password);
        if (!user.has_value()) {
            std::cout << "Login failed, please try again.\n";
        }
    }

    if (!user.has_value()) {
        std::cout << "Too many tries. Goodbye.\n";
        return 1;
    }

    std::cout << "Welcome, " << user->getUsername() << "!\n";

    // now build the student layers and tell the service my role so it know
    // if i can write or only read
    StudentService service(studentRepo);
    service.setRole(user->getRole());
    StudentController controller(service, *user);

    controller.run();
    return 0;
}
/* emily cruz was here :) */
