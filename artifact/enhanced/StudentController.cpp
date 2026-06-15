// =============================================================
//  Student Portal — StudentController.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     implement the menu and all the handlers, including the new
//              module 5 options and the reports submenu.
// =============================================================
#include "StudentController.h"
#include <iostream>
#include <limits>
#include <vector>

StudentController::StudentController(StudentService& svc, const User& user)
    : service(svc), currentUser(user) {
}

// small helper to print a list of students or a message when is empty
static void printList(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students match.\n";
        return;
    }
    for (const Student& s : students) {
        s.printDetails();
    }
}

void StudentController::displayMenu() const {
    std::cout << "\n--- Student Portal (Enhanced) ---\n";
    std::cout << "Logged in as: " << currentUser.getUsername()
              << " (" << roleToString(currentUser.getRole()) << ")\n";
    std::cout << "1. Add Student        [admin]\n";
    std::cout << "2. Search Student by ID\n";
    std::cout << "3. Display All Students\n";
    std::cout << "4. Update Student     [admin]\n";
    std::cout << "5. Delete Student     [admin]\n";
    std::cout << "6. Search by Name\n";
    std::cout << "7. Search by GPA Range\n";
    std::cout << "8. Reports\n";
    std::cout << "9. Exit\n";
    std::cout << "Select an option: ";
}

void StudentController::handleAddStudent() {
    int id;
    std::string name;
    double gpa;

    std::cout << "Enter ID: ";
    std::cin >> id;
    std::cout << "Enter Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter GPA: ";
    std::cin >> gpa;

    std::string error;
    // i ask the service to add. if the data is bad OR i am not admin, it
    // give me the reason and i show it instead of saving a wrong student
    if (service.addStudent(id, name, gpa, error)) {
        std::cout << "Student add ok!\n";
    } else {
        std::cout << "Can not add student: " << error << "\n";
    }
}

void StudentController::handleSearchStudent() {
    int searchId;
    std::cout << "Enter ID: ";
    std::cin >> searchId;

    auto found = service.findStudent(searchId);
    if (found.has_value()) {
        found.value().printDetails();
    } else {
        std::cout << "Student not found.\n";
    }
}

void StudentController::handleDisplayAll() const {
    auto students = service.getAllStudents();
    if (students.empty()) {
        std::cout << "No students yet, please add some first.\n";
        return;
    }
    for (const Student& s : students) {
        s.printDetails();
    }
}

// module 5: update. i ask the new name and gpa and pass to the service. the
// service check i am admin and that the id exist
void StudentController::handleUpdateStudent() {
    int id;
    std::string name;
    double gpa;

    std::cout << "Enter ID to update: ";
    std::cin >> id;
    std::cout << "Enter new Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter new GPA: ";
    std::cin >> gpa;

    std::string error;
    if (service.updateStudent(id, name, gpa, error)) {
        std::cout << "Student update ok!\n";
    } else {
        std::cout << "Can not update: " << error << "\n";
    }
}

// module 5: delete by id
void StudentController::handleDeleteStudent() {
    int id;
    std::cout << "Enter ID to delete: ";
    std::cin >> id;

    std::string error;
    if (service.deleteStudent(id, error)) {
        std::cout << "Student delete ok!\n";
    } else {
        std::cout << "Can not delete: " << error << "\n";
    }
}

// module 5: search by a part of the name
void StudentController::handleSearchByName() {
    std::string part;
    std::cout << "Enter part of the name: ";
    std::cin.ignore();
    std::getline(std::cin, part);
    printList(service.searchByName(part));
}

// module 5: search by gpa range
void StudentController::handleSearchByGpaRange() {
    double minGpa, maxGpa;
    std::cout << "Enter min GPA: ";
    std::cin >> minGpa;
    std::cout << "Enter max GPA: ";
    std::cin >> maxGpa;
    printList(service.searchByGpaRange(minGpa, maxGpa));
}

// module 5: a little reports menu. dean's list, total and average
void StudentController::handleReports() const {
    std::cout << "\n-- Reports --\n";
    std::cout << "1. Dean's List (GPA >= 3.5)\n";
    std::cout << "2. Total students\n";
    std::cout << "3. Average GPA\n";
    std::cout << "Select a report: ";

    int r = 0;
    if (!(std::cin >> r)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Please put a number.\n";
        return;
    }

    if (r == 1) {
        std::cout << "Dean's List:\n";
        printList(service.deansList(3.5));
    } else if (r == 2) {
        std::cout << "Total students: " << service.studentCount() << "\n";
    } else if (r == 3) {
        std::cout << "Average GPA: " << service.averageGpa() << "\n";
    } else {
        std::cout << "That report no exist.\n";
    }
}

void StudentController::run() {
    int choice = 0;

    while (true) {
        displayMenu();

        // if the person type a letter and not a number, cin break. so i
        // clean it and ask again, before this could make a infinite loop
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please put a number from the menu.\n";
            continue;
        }

        if (choice == 1) {
            handleAddStudent();
        } else if (choice == 2) {
            handleSearchStudent();
        } else if (choice == 3) {
            handleDisplayAll();
        } else if (choice == 4) {
            handleUpdateStudent();
        } else if (choice == 5) {
            handleDeleteStudent();
        } else if (choice == 6) {
            handleSearchByName();
        } else if (choice == 7) {
            handleSearchByGpaRange();
        } else if (choice == 8) {
            handleReports();
        } else if (choice == 9) {
            std::cout << "Bye bye, thank you for use the portal!\n";
            break;   // we just break the loop, everything clean itself, no leak
        } else {
            std::cout << "That option no exist, please try again.\n";
        }
    }
}
/* emily cruz was here :) */
