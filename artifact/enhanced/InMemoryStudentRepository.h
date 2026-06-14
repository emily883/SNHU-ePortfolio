#ifndef IN_MEMORY_STUDENT_REPOSITORY_H
#define IN_MEMORY_STUDENT_REPOSITORY_H

#include "StudentRepository.h"

// this repo keep the students in memory inside a vector, same like the
// original program was doing. for module three i keep it in memory on
// purpose, the real database come later in module five. when that happen
// i only make other class that implement IStudentRepository, easy
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
};

#endif
/* emily cruz was here :) */
