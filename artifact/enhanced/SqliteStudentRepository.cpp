// =============================================================
//  Student Portal — SqliteStudentRepository.cpp
//  Programmer: Emily Cruz
//  Date:       2026-06-15
//  Version:    3.0 (Module 5 — Databases enhancement)
//  Intent:     SQLite implementation. all the sql use prepared statements
//              and bind, so the values are data, never code (no injection).
// =============================================================
#include "SqliteStudentRepository.h"

#include <stdexcept>

// small helper to read one row (id, name, gpa) into a Student object. i use
// it in every select so i no repeat the same code
static Student readRow(sqlite3_stmt* stmt) {
    int id = sqlite3_column_int(stmt, 0);
    const unsigned char* name = sqlite3_column_text(stmt, 1);
    double gpa = sqlite3_column_double(stmt, 2);
    return Student(id, name ? reinterpret_cast<const char*>(name) : "", gpa);
}

// open the file and create the table if is not there. open with the path
// they give me (not hardcoded). if it fail i throw because there is no
// point to continue without the database
SqliteStudentRepository::SqliteStudentRepository(const std::string& dbPath) {
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        throw std::runtime_error("can not open student database");
    }
    const char* ddl =
        "CREATE TABLE IF NOT EXISTS students ("
        " id INTEGER PRIMARY KEY,"
        " name TEXT NOT NULL,"
        " gpa REAL NOT NULL);";
    char* err = nullptr;
    if (sqlite3_exec(db, ddl, nullptr, nullptr, &err) != SQLITE_OK) {
        std::string msg = err ? err : "unknown";
        sqlite3_free(err);
        throw std::runtime_error("can not create students table: " + msg);
    }
}

SqliteStudentRepository::~SqliteStudentRepository() {
    sqlite3_close(db);   // close the connection, no leak
}

// INSERT with ? marks. i bind the real values after, so even if the name
// have a quote or weird sql inside, it is only text, it can not break query
void SqliteStudentRepository::add(const Student& student) {
    const char* sql = "INSERT INTO students (id, name, gpa) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }
    sqlite3_bind_int(stmt, 1, student.getId());
    sqlite3_bind_text(stmt, 2, student.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, student.getGpa());
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

std::optional<Student> SqliteStudentRepository::findById(int id) const {
    const char* sql = "SELECT id, name, gpa FROM students WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    std::optional<Student> result;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            result = readRow(stmt);
        }
    }
    sqlite3_finalize(stmt);
    return result;
}

// the database give them back already in order by id (ORDER BY), so the
// display all come out sorted, same like the memory repo in module 4
std::vector<Student> SqliteStudentRepository::getAll() const {
    std::vector<Student> out;
    const char* sql = "SELECT id, name, gpa FROM students ORDER BY id;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            out.push_back(readRow(stmt));
        }
    }
    sqlite3_finalize(stmt);
    return out;
}

void SqliteStudentRepository::update(const Student& student) {
    const char* sql = "UPDATE students SET name = ?, gpa = ? WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }
    sqlite3_bind_text(stmt, 1, student.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, student.getGpa());
    sqlite3_bind_int(stmt, 3, student.getId());
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

void SqliteStudentRepository::remove(int id) {
    const char* sql = "DELETE FROM students WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return;
    }
    sqlite3_bind_int(stmt, 1, id);
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}

// search by part of the name with LIKE. i put the % around the word and i
// BIND it (i no glue it in the string), so it is safe from injection
std::vector<Student> SqliteStudentRepository::findByName(const std::string& part) const {
    std::vector<Student> out;
    const char* sql =
        "SELECT id, name, gpa FROM students WHERE name LIKE ? ORDER BY name;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string pattern = "%" + part + "%";
        sqlite3_bind_text(stmt, 1, pattern.c_str(), -1, SQLITE_TRANSIENT);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            out.push_back(readRow(stmt));
        }
    }
    sqlite3_finalize(stmt);
    return out;
}

// students with gpa between min and max, best first. the database do the
// WHERE and the ORDER BY for me, that is the power of sql
std::vector<Student> SqliteStudentRepository::findByGpaRange(double minGpa,
                                                             double maxGpa) const {
    std::vector<Student> out;
    const char* sql =
        "SELECT id, name, gpa FROM students "
        "WHERE gpa BETWEEN ? AND ? ORDER BY gpa DESC, id;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, minGpa);
        sqlite3_bind_double(stmt, 2, maxGpa);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            out.push_back(readRow(stmt));
        }
    }
    sqlite3_finalize(stmt);
    return out;
}

// COUNT(*) — the database count for me, i no bring all the rows just to
// count them, that is more efficient
int SqliteStudentRepository::count() const {
    const char* sql = "SELECT COUNT(*) FROM students;";
    sqlite3_stmt* stmt = nullptr;
    int n = 0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            n = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return n;
}

// AVG(gpa) — if the table is empty AVG give NULL, so i check the type and
// return 0 in that case to no crash
double SqliteStudentRepository::averageGpa() const {
    const char* sql = "SELECT AVG(gpa) FROM students;";
    sqlite3_stmt* stmt = nullptr;
    double avg = 0.0;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW
            && sqlite3_column_type(stmt, 0) != SQLITE_NULL) {
            avg = sqlite3_column_double(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
    return avg;
}
/* emily cruz put the students in a real database now :) */
