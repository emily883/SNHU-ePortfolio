// =============================================================
//  Student Portal — StudentRepository.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     interface (contract) for any student storage. module 5
//              adds update/delete, search by criteria, and reports so a
//              database repo and the memory repo both follow the same shape.
// =============================================================
#ifndef STUDENT_REPOSITORY_H
#define STUDENT_REPOSITORY_H

#include <vector>
#include <optional>
#include <string>
#include "Student.h"

// this is only the contract (interface), like a promise of what any repo
// must can do. i make it abstract on purpose: the database repo and the
// memory repo both implement this, and the service no need to change. that
// is the repository pattern, very useful
class IStudentRepository {
public:
    virtual ~IStudentRepository() = default;

    // ---- basic (module 3/4) ----
    virtual void add(const Student& student) = 0;
    virtual std::optional<Student> findById(int id) const = 0;
    virtual std::vector<Student> getAll() const = 0;

    // ---- module 5: full CRUD (the U and the D) ----
    virtual void update(const Student& student) = 0;   // change name/gpa of an id
    virtual void remove(int id) = 0;                   // delete by id

    // ---- module 5: search by criteria ----
    virtual std::vector<Student> findByName(const std::string& part) const = 0;       // partial match
    virtual std::vector<Student> findByGpaRange(double minGpa, double maxGpa) const = 0;

    // ---- module 5: reports / aggregates ----
    virtual int count() const = 0;
    virtual double averageGpa() const = 0;
};

#endif
/* emily cruz was here too :) */
