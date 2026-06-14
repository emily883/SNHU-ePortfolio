#ifndef STUDENT_CONTROLLER_H
#define STUDENT_CONTROLLER_H

#include "StudentService.h"

// the controller is the part that talk with the person. it show the menu,
// read what they type, and ask the service to do the work. it no save
// nothing by itself and it no know about the repository, only the service
class StudentController {
private:
    StudentService& service;   // also inject from outside, same idea

    void displayMenu() const;
    void handleAddStudent();
    void handleSearchStudent();
    void handleDisplayAll() const;

public:
    explicit StudentController(StudentService& svc);
    void run();   // the big loop that keep asking until the person exit
};

#endif
/* emily cruz was here :) */
