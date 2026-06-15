// =============================================================
//  Student Portal — StudentService.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     business rules layer. module 5 adds update/delete with
//              validation, search by criteria, reports, and the access
//              control (only admin can write).
// =============================================================
#ifndef STUDENT_SERVICE_H
#define STUDENT_SERVICE_H

#include <string>
#include <vector>
#include "StudentRepository.h"
#include "User.h"

// the service is like the brain. it check all the rules before we save
// any student. it talk to the repository but it no know (and no care) if
// the repo is memory or a database, it only use the interface.
//
// module 5: the service also know the role of who is logged in, and it is
// the one who say NO to a normal user that try to write. i put the rule
// here (not only in the menu) because the menu is just the face, the real
// guard must be in the logic so nobody can pass around it
class StudentService {
private:
    IStudentRepository& repository;   // the repo come from outside (injection)
    Role role = Role::User;           // least privilege until login tell me more

    // shared checks so add and update no repeat the same code
    bool validateFields(const std::string& name, double gpa, std::string& error) const;
    // the gate: return false (and fill error) if the current role is not admin
    bool requireAdmin(std::string& error) const;

public:
    explicit StudentService(IStudentRepository& repo);

    // after the login, main tell the service what role the user have
    void setRole(Role r);

    // ---- write operations (admin only) ----
    bool addStudent(int id, const std::string& name, double gpa, std::string& error);
    bool updateStudent(int id, const std::string& name, double gpa, std::string& error);
    bool deleteStudent(int id, std::string& error);

    // ---- read operations (everybody) ----
    std::optional<Student> findStudent(int id) const;
    std::vector<Student> getAllStudents() const;
    std::vector<Student> searchByName(const std::string& part) const;
    std::vector<Student> searchByGpaRange(double minGpa, double maxGpa) const;

    // ---- reports ----
    std::vector<Student> deansList(double threshold) const;   // gpa >= threshold
    int studentCount() const;
    double averageGpa() const;
};

#endif
/* emily cruz was here :) */
