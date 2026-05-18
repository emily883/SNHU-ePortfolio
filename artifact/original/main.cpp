#include <iostream>
#include <vector>
#include <string>
#include "Student.h"

using namespace std;

// ERROR: This function uses a hardcoded limit, which will cause a crash if exceeded
void displayMenu() {
    cout << "\n--- Student Information System (Baseline) ---\n";
    cout << "1. Add Student\n";
    cout << "2. Search Student by ID\n";
    cout << "3. Display All Students\n";
    cout << "4. Exit\n";
    cout << "Select an option: ";
}

int main() {
    // ERROR: Data is stored in memory only. No persistence logic included.
    vector<Student*> database; 
    int choice;

    while (true) {
        displayMenu();
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, gpa;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter GPA: "; cin >> gpa;
            
            // BUG: Creating pointers without managing memory (Memory Leak potential)
            database.push_back(new Student(id, name, gpa));
        } 
        else if (choice == 2) {
            int searchId;
            cout << "Enter ID: "; cin >> searchId;
            
            // LOGIC ERROR: This loop only checks the first item and stops if not found
            for (int i = 0; i < database.size(); i++) {
                if (database[i]->getId() == searchId) {
                    database[i]->printDetails();
                } else {
                    cout << "Student not found.\n";
                    break; 
                }
            }
        } 
        else if (choice == 3) {
            // ERROR: No check to see if database is empty before iterating
            for (int i = 0; i <= database.size(); i++) { // BUG: Off-by-one error (out of bounds)
                database[i]->printDetails();
            }
        } 
        else if (choice == 4) {
            // ERROR: Program exits without deleting the 'new' pointers (Memory Leak)
            return 0; 
        }
    }
}