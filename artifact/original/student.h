#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public: // ERROR: Data members should be private (Encapsulation violation)
    int id;
    std::string name;
    std::string gpa;

    Student(int id, std::string name, std::string gpa);
    int getId() const;
    void printDetails() const;
};

#endif