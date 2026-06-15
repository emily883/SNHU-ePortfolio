// =============================================================
//  Student Portal — SqliteStudentRepository.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     store the students in a real SQLite database so the data
//              stay saved between runs. every query is parameterized.
// =============================================================
#ifndef SQLITE_STUDENT_REPOSITORY_H
#define SQLITE_STUDENT_REPOSITORY_H

#include "StudentRepository.h"
#include <sqlite3.h>

// this repo save the students in a sqlite file (students.db). before, in
// module 3/4, everything was in memory and lost when you close. now it is
// persistent. it implement the same IStudentRepository so the service and
// the controller no change anything :)
class SqliteStudentRepository : public IStudentRepository {
private:
    sqlite3* db = nullptr;

public:
    // the path of the db file come from outside (not hardcoded), default
    // is "students.db". this start the security idea: config, not glue
    explicit SqliteStudentRepository(const std::string& dbPath);
    ~SqliteStudentRepository() override;

    void add(const Student& student) override;
    std::optional<Student> findById(int id) const override;
    std::vector<Student> getAll() const override;

    void update(const Student& student) override;
    void remove(int id) override;

    std::vector<Student> findByName(const std::string& part) const override;
    std::vector<Student> findByGpaRange(double minGpa, double maxGpa) const override;

    int count() const override;
    double averageGpa() const override;
};

#endif
/* emily cruz put the students in a real database now :) */
