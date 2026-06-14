#ifndef STUDENT_REPOSITORY_H
#define STUDENT_REPOSITORY_H

#include <vector>
#include <optional>
#include "Student.h"

// this is only the contract (interface), like a promise of what any repo
// must can do. i make it abstract on purpose: in module five i will make
// a database repository and the service no need to change nothing, it only
// talk to this interface. that is the repository pattern, very useful
class IStudentRepository {
public:
    virtual ~IStudentRepository() = default;

    virtual void add(const Student& student) = 0;
    virtual std::optional<Student> findById(int id) const = 0;
    virtual std::vector<Student> getAll() const = 0;
};

#endif
/* emily cruz was here too :) */
