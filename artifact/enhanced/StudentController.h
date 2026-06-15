// =============================================================
//  Student Portal — StudentController.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     menu and input/output. module 5 adds update, delete,
//              search by name/gpa, a reports submenu, and shows who is
//              logged in (admin options marked).
// =============================================================
#ifndef STUDENT_CONTROLLER_H
#define STUDENT_CONTROLLER_H

#include "StudentService.h"
#include "User.h"

// the controller is the part that talk with the person. it show the menu,
// read what they type, and ask the service to do the work. it no save
// nothing by itself and it no know about the repository, only the service.
//
// module 5: it also keep who is logged in, to greet and to mark the admin
// options. but remember: hiding the option is only for nice UX, the REAL
// block is in the service
class StudentController {
private:
    StudentService& service;
    User currentUser;   // who is logged in

    void displayMenu() const;
    void handleAddStudent();
    void handleSearchStudent();
    void handleDisplayAll() const;
    void handleUpdateStudent();
    void handleDeleteStudent();
    void handleSearchByName();
    void handleSearchByGpaRange();
    void handleReports() const;

public:
    StudentController(StudentService& svc, const User& user);
    void run();   // the big loop that keep asking until the person exit
};

#endif
/* emily cruz was here :) */
