#include "Student.h"
#include <iostream>
#include <iomanip>

// the constructor only keep the values now. the checking (negative id,
// bad gpa) is do by the service before, so when we get here is already ok
Student::Student(int id, std::string name, double gpa) {
    this->id = id;
    this->name = name;
    this->gpa = gpa;
}

int Student::getId() const {
    return id;
}

std::string Student::getName() const {
    return name;
}

double Student::getGpa() const {
    return gpa;
}

// before this print throw everything together and was very hard to read.
// now i put labels and only two decimal for the gpa so it look clean
void Student::printDetails() const {
    std::cout << "ID: " << id
              << " | Name: " << name
              << " | GPA: " << std::fixed << std::setprecision(2) << gpa
              << std::endl;
}
/* emily cruz make this part :) */
