#include "InMemoryStudentRepository.h"

// i push the student inside the vector. before the program use "new" and
// never delete, so it was leaking memory. now is a value, no leak anymore
void InMemoryStudentRepository::add(const Student& student) {
    students.push_back(student);
}

// the old search was broken, it check only the first student and if that
// one was not the id it say "not found" and stop. here i look ALL of them
// and only if nobody match i return nothing (nullopt)
std::optional<Student> InMemoryStudentRepository::findById(int id) const {
    for (const Student& s : students) {
        if (s.getId() == id) {
            return s;
        }
    }
    return std::nullopt;   // i check everybody first, then i say not found
}

// give back a copy of all the students so the controller can print them
std::vector<Student> InMemoryStudentRepository::getAll() const {
    return students;
}
/* emily cruz code this part :) */
