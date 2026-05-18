#include "Student.h"
#include <iostream>

// ERROR: Constructor does not validate data (e.g., negative IDs or invalid GPAs)
Student::Student(int id, std::string name, std::string gpa) {
    this->id = id;
    this->name = name;
    this->gpa = gpa;
}

int Student::getId() const {
    return id;
}

void Student::printDetails() const {
    // BUG: Missing basic formatting, making the output hard to read
    std::cout << id << name << gpa << std::endl;
}