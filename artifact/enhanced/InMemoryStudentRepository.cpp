#include "InMemoryStudentRepository.h"
#include <algorithm>

// little helper: if the vector is dirty (somebody add after last sort) i
// sort it one time by id. i use stable_sort so if two key was equal they
// keep the order they came in. right now the id is unique so it no really
// matter, but is the safe choice if later i sort by other thing like name
void InMemoryStudentRepository::ensureSorted() const {
    if (!sorted) {
        std::stable_sort(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getId() < b.getId();
            });
        sorted = true;
    }
}

// i just push at the end, that is cheap (O(1)). i no sort here, i only mark
// dirty. this is the trade-off: add is fast, and i pay the sort later, one
// time, before the first search. if i add many student in a row i only sort
// once at the end, not every time
void InMemoryStudentRepository::add(const Student& student) {
    students.push_back(student);
    sorted = false;   // now is dirty, next search will sort first
}

// before (module three) this was linear, it look one by one (O(n)). now i
// make sure is sorted and use lower_bound, that is binary search (O(log n)).
// lower_bound give me the first student with id >= the one i look, then i
// only check if that one is exactly my id
std::optional<Student> InMemoryStudentRepository::findById(int id) const {
    ensureSorted();

    auto it = std::lower_bound(students.begin(), students.end(), id,
        [](const Student& s, int target) {
            return s.getId() < target;
        });

    if (it != students.end() && it->getId() == id) {
        return *it;
    }
    return std::nullopt;   // not there, but now i find it fast, no look all
}

// give back a copy of all the students so the controller can print them.
// i sort first so the "display all" come out nice in order by id, that is
// a free bonus from keeping the vector sorted
std::vector<Student> InMemoryStudentRepository::getAll() const {
    ensureSorted();
    return students;
}
/* emily cruz make the search faster here :) */
