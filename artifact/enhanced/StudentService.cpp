// =============================================================
//  Student Portal — StudentService.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     implement validation, access control, and the new module 5
//              operations (update/delete, search, reports).
// =============================================================
#include "StudentService.h"

// we save the repo by reference, this is dependency injection. the service
// no make the repo by itself, somebody give it from outside (the main)
StudentService::StudentService(IStudentRepository& repo) : repository(repo) {
}

void StudentService::setRole(Role r) {
    role = r;
}

// the access gate. if the role is not admin i say no. i put this in the
// service so it protect EVERY write, no matter from where they call it
bool StudentService::requireAdmin(std::string& error) const {
    if (role != Role::Admin) {
        error = "only an admin can do this, you are read-only";
        return false;
    }
    return true;
}

// the field checks, same for add and update so i no write it two time. this
// is the security mindset: never trust the input, validate first
bool StudentService::validateFields(const std::string& name, double gpa,
                                    std::string& error) const {
    if (name.empty()) {
        error = "name is empty, please write a name";
        return false;
    }
    if (gpa < 0.0 || gpa > 4.0) {
        error = "gpa must be between 0.0 and 4.0";
        return false;
    }
    return true;
}

bool StudentService::addStudent(int id, const std::string& name, double gpa,
                                std::string& error) {
    if (!requireAdmin(error)) {
        return false;
    }
    if (id < 0) {
        error = "id can not be negative";
        return false;
    }
    if (!validateFields(name, gpa, error)) {
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

// module 5: update. only admin, and the id must already exist (you can not
// update somebody that is not there)
bool StudentService::updateStudent(int id, const std::string& name, double gpa,
                                   std::string& error) {
    if (!requireAdmin(error)) {
        return false;
    }
    if (!repository.findById(id).has_value()) {
        error = "no student with that id, nothing to update";
        return false;
    }
    if (!validateFields(name, gpa, error)) {
        return false;
    }

    repository.update(Student(id, name, gpa));
    return true;
}

// module 5: delete. only admin, and the id must exist
bool StudentService::deleteStudent(int id, std::string& error) {
    if (!requireAdmin(error)) {
        return false;
    }
    if (!repository.findById(id).has_value()) {
        error = "no student with that id, nothing to delete";
        return false;
    }

    repository.remove(id);
    return true;
}

std::optional<Student> StudentService::findStudent(int id) const {
    return repository.findById(id);
}

std::vector<Student> StudentService::getAllStudents() const {
    return repository.getAll();
}

std::vector<Student> StudentService::searchByName(const std::string& part) const {
    return repository.findByName(part);
}

std::vector<Student> StudentService::searchByGpaRange(double minGpa, double maxGpa) const {
    return repository.findByGpaRange(minGpa, maxGpa);
}

// the dean's list is just the students with gpa from the threshold up to
// the max (4.0). i reuse the range search, no need new code
std::vector<Student> StudentService::deansList(double threshold) const {
    return repository.findByGpaRange(threshold, 4.0);
}

int StudentService::studentCount() const {
    return repository.count();
}

double StudentService::averageGpa() const {
    return repository.averageGpa();
}
/* emily cruz make the rules here :) */
