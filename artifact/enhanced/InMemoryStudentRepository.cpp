// =============================================================
//  Student Portal — InMemoryStudentRepository.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     vector implementation of the repository, now with the
//              module 5 CRUD + criteria search + reports.
// =============================================================
#include "InMemoryStudentRepository.h"
#include <algorithm>
#include <cctype>

// little helper: does "text" contain "part", ignoring upper/lower case.
// i lower both and use find. is simple but enough for a name search
static bool containsNoCase(const std::string& text, const std::string& part) {
    std::string a = text, b = part;
    std::transform(a.begin(), a.end(), a.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    std::transform(b.begin(), b.end(), b.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return a.find(b) != std::string::npos;
}

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

// module 5: update. i find the one with the id and put a new Student in his
// place with the new name/gpa. the id no change so the order stay the same
void InMemoryStudentRepository::update(const Student& student) {
    for (Student& s : students) {
        if (s.getId() == student.getId()) {
            s = student;
            return;
        }
    }
}

// module 5: delete. i erase the one with that id from the vector
void InMemoryStudentRepository::remove(int id) {
    students.erase(
        std::remove_if(students.begin(), students.end(),
            [id](const Student& s) { return s.getId() == id; }),
        students.end());
}

// module 5: give all the students that have the part inside the name
std::vector<Student> InMemoryStudentRepository::findByName(const std::string& part) const {
    ensureSorted();
    std::vector<Student> out;
    for (const Student& s : students) {
        if (containsNoCase(s.getName(), part)) {
            out.push_back(s);
        }
    }
    return out;
}

// module 5: students with gpa inside the range
std::vector<Student> InMemoryStudentRepository::findByGpaRange(double minGpa,
                                                               double maxGpa) const {
    std::vector<Student> out;
    for (const Student& s : students) {
        if (s.getGpa() >= minGpa && s.getGpa() <= maxGpa) {
            out.push_back(s);
        }
    }
    // best gpa first, so it match the database repo order
    std::stable_sort(out.begin(), out.end(),
        [](const Student& a, const Student& b) { return a.getGpa() > b.getGpa(); });
    return out;
}

// module 5: how many students
int InMemoryStudentRepository::count() const {
    return static_cast<int>(students.size());
}

// module 5: the average gpa. if no students i return 0 so i no divide by 0
double InMemoryStudentRepository::averageGpa() const {
    if (students.empty()) {
        return 0.0;
    }
    double total = 0.0;
    for (const Student& s : students) {
        total += s.getGpa();
    }
    return total / students.size();
}
/* emily cruz make the search faster here :) */
