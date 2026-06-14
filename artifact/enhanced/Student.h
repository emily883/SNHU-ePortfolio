#ifndef STUDENT_H
#define STUDENT_H

#include <string>

// this is the student model. before all the data was public and anybody
// could change it from outside, that was not safe. now i keep it private
class Student {
private:
    int id;
    std::string name;
    double gpa;   // before this was a string, but gpa is a number so now double

public:
    Student(int id, std::string name, double gpa);

    // getters only, they read the value but no change it (that is why const)
    int getId() const;
    std::string getName() const;
    double getGpa() const;

    // print the student nice with labels, before was all stick together
    void printDetails() const;
};

#endif
/* emily cruz was here :) */
