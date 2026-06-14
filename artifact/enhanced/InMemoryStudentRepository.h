#ifndef IN_MEMORY_STUDENT_REPOSITORY_H
#define IN_MEMORY_STUDENT_REPOSITORY_H

#include "StudentRepository.h"

// this repo keep the students in memory inside a vector, same like the
// original program was doing. for module three i keep it in memory on
// purpose, the real database come later in module five. when that happen
// i only make other class that implement IStudentRepository, easy
class InMemoryStudentRepository : public IStudentRepository {
private:
    std::vector<Student> students;   // all the students live here, in memory only

public:
    void add(const Student& student) override;
    std::optional<Student> findById(int id) const override;
    std::vector<Student> getAll() const override;
};

#endif
/* emily cruz was here :) */
