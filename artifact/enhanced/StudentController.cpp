#include "StudentController.h"
#include <iostream>
#include <limits>

StudentController::StudentController(StudentService& svc) : service(svc) {
}

void StudentController::displayMenu() const {
    std::cout << "\n--- Student Portal (Enhanced) ---\n";
    std::cout << "1. Add Student\n";
    std::cout << "2. Search Student by ID\n";
    std::cout << "3. Display All Students\n";
    std::cout << "4. Exit\n";
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
    // i ask the service to add. if the data is bad, it give me the reason
    // and i show it to the person instead of saving a wrong student
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

    // before, the search stop on the first student. now the service look
    // all of them, so this work good even if the id is the last one
    auto found = service.findStudent(searchId);
    if (found.has_value()) {
        found.value().printDetails();
    } else {
        std::cout << "Student not found.\n";
    }
}

void StudentController::handleDisplayAll() const {
    auto students = service.getAllStudents();

    // before there was no empty check and the loop go one position extra
    // (i <= size) so it read out of the vector and crash. both fix now
    if (students.empty()) {
        std::cout << "No students yet, please add some first.\n";
        return;
    }

    for (const Student& s : students) {
        s.printDetails();
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
            std::cout << "Bye bye, thank you for use the portal!\n";
            break;   // we just break the loop, the vector clean itself, no leak
        } else {
            std::cout << "That option no exist, please try again.\n";
        }
    }
}
/* emily cruz was here :) */
