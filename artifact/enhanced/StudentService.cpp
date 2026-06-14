#include "StudentService.h"

// we save the repo by reference, this is dependency injection. the service
// no make the repo by itself, somebody give it from outside (the main)
StudentService::StudentService(IStudentRepository& repo) : repository(repo) {
}

// here i check everything that the old program never check. this is also
// part of the security mindset: never trust the input, validate first
bool StudentService::addStudent(int id, const std::string& name, double gpa, std::string& error) {
    if (id < 0) {
        error = "id can not be negative";
        return false;
    }
    if (name.empty()) {
        error = "name is empty, please write a name";
        return false;
    }
    if (gpa < 0.0 || gpa > 4.0) {
        error = "gpa must be between 0.0 and 4.0";
        return false;
    }
    // no two students with same id, that would be confuse
    if (repository.findById(id).has_value()) {
        error = "that id already exist, please choose other one";
        return false;
    }

    repository.add(Student(id, name, gpa));
    return true;
}

std::optional<Student> StudentService::findStudent(int id) const {
    return repository.findById(id);
}

std::vector<Student> StudentService::getAllStudents() const {
    return repository.getAll();
}
/* emily cruz make the rules here :) */
