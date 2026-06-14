#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include <string>
#include "StudentRepository.h"

// the service is like the brain. it check all the rules before we save
// any student. it talk to the repository but it no know (and no care) if
// the repo is memory or a database, it only use the interface
class StudentService {
private:
    IStudentRepository& repository;   // the repo come from outside (injection)

public:
    explicit StudentService(IStudentRepository& repo);

    // return true if the student was add ok. if not, "error" tell why
    bool addStudent(int id, const std::string& name, double gpa, std::string& error);

    std::optional<Student> findStudent(int id) const;
    std::vector<Student> getAllStudents() const;
};

#endif
/* emily cruz was here :) */
