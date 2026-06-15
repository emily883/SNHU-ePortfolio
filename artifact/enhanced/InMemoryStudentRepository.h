// =============================================================
//  Student Portal — InMemoryStudentRepository.h
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     in-memory version of the repository. still here so the
//              architecture keeps two implementations of the same contract
//              (good for fast tests); module 5 adds CRUD + criteria here too.
// =============================================================
#ifndef IN_MEMORY_STUDENT_REPOSITORY_H
#define IN_MEMORY_STUDENT_REPOSITORY_H

#include "StudentRepository.h"

// this repo keep the students in memory inside a vector, same like the
// original program was doing. the sqlite repo is the real one for module 5,
// but i keep this one alive because it implement the SAME interface, so it
// prove the repository pattern work and it is handy for quick test.
//
// for module four i make the search faster: i keep the vector sorted by id
// so findById can use binary search (log n) instead of look one by one.
class InMemoryStudentRepository : public IStudentRepository {
private:
    // i mark this mutable because findById/getAll are const but i still
    // want to sort the vector inside them the first time (lazy sort). the
    // student no see any difference, the data is the same, only the order
    mutable std::vector<Student> students;   // all the students, in memory only
    mutable bool sorted = true;              // false when somebody add and i no sort yet

    // sort only if is dirty, and only one time until next add. i put it
    // const so the const methods can call it (it no change what we store,
    // only the order)
    void ensureSorted() const;

public:
    void add(const Student& student) override;
    std::optional<Student> findById(int id) const override;
    std::vector<Student> getAll() const override;

    // module 5: same new operations as the database repo, but on the vector
    void update(const Student& student) override;
    void remove(int id) override;
    std::vector<Student> findByName(const std::string& part) const override;
    std::vector<Student> findByGpaRange(double minGpa, double maxGpa) const override;
    int count() const override;
    double averageGpa() const override;
};

#endif
/* emily cruz was here :) */
