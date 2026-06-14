# Enhancement One Narrative — Software Design and Engineering

**Course:** CS-499 Computer Science Capstone — Southern New Hampshire University
**Student:** Emily Cruz
**Category:** Software Design and Engineering (Module Three)
**Artifact:** Student Portal (C++)

## Description and Origin of the Artifact

The artifact is the **Student Portal**, a C++ console application originally
provided as starter code by Dr. Bolton for CS-499 (Option B: Medical/Student
Information Portal). In its baseline form (`artifact/original/`) the program is a
small "Student Information System" that lets a user add students, search a student
by ID, and display all students. The data lives only in memory.

The same artifact is being enhanced across all three capstone categories. This
narrative covers the **first enhancement: Software Design and Engineering**. The
enhanced version lives in `artifact/enhanced/` so the original is preserved for a
clear before/after comparison.

## Justification for Inclusion

I selected this artifact for the Software Design and Engineering category because
the baseline was a single, monolithic `main.cpp` where the user interface, the
data storage, and the (missing) validation were all tangled together. That made
it a strong candidate to demonstrate **architectural design skills** by
restructuring it into a clean, layered design.

The enhancement showcases:

- **Layered architecture — Controller / Service / Repository.** Responsibilities
  are now separated. The `StudentController` handles all user interaction, the
  `StudentService` holds the business rules and validation, and the
  `IStudentRepository` defines how data is stored and retrieved.
- **The Repository pattern with an interface (`IStudentRepository`).** The current
  implementation, `InMemoryStudentRepository`, keeps the data in a `std::vector`
  in memory — exactly the way the original program stored it. This is intentional:
  the **real database belongs to a later enhancement (Module Five — Databases)**.
  Because storage sits behind an interface, that future database implementation
  can be swapped in without changing the service or the controller.
- **Dependency injection.** `main.cpp` is the single place that wires the layers
  together (repository → service → controller). It is the only location that needs
  to change when the in-memory repository is later replaced by a database-backed
  one.
- **Encapsulation.** The `Student` model now has private data members with `const`
  getters, fixing the encapsulation violation in the original.
- **Memory safety (security mindset).** The baseline used raw `new` without ever
  calling `delete`, leaking memory. The enhanced version uses value semantics
  (`std::vector<Student>`), so there are no manual allocations and no leaks.
- **Input validation (security mindset).** The service rejects negative IDs, empty
  names, GPAs outside the 0.0–4.0 range, and duplicate IDs — none of which the
  baseline checked.

### Architecture diagram

```mermaid
flowchart TD
    User([User]) <--> Controller[StudentController<br/>menu & I/O]
    Controller --> Service[StudentService<br/>business rules & validation]
    Service --> Repo[/IStudentRepository<br/>interface/]
    Repo --> Mem[InMemoryStudentRepository<br/>std::vector in memory]
    Repo -. Module Five .-> DB[(Future DB repository)]
```

## Defects Corrected

Beyond the architectural redesign, the enhancement fixes the concrete defects
that were marked in the baseline:

| Baseline issue | Fix in the enhanced version |
| --- | --- |
| Public data members (`student.h`) | Private members + `const` getters |
| Constructor did not validate data | Validation centralized in `StudentService` |
| `printDetails` had no formatting | Labeled, fixed-precision output |
| Memory leak from raw `new` | Value semantics (`std::vector<Student>`) |
| Search only checked the first item | `findById` iterates the whole collection |
| Off-by-one (`i <= size()`) out-of-bounds in "display all" | Range-based loop + empty check |
| Invalid menu input could loop forever | Stream error handling in the menu loop |

## Reflection — Course Outcomes

This enhancement supports Outcome 4 (using well-founded techniques and tools in
computing practice) and Outcome 5 (a security mindset).

Designing the service against the `IStudentRepository` interface, instead of
against a concrete class, decouples the business logic from the storage
mechanism. Once the repository sits behind that interface, the rest of the code
does not depend on how the data is stored. The in-memory repository can then be
replaced by a database implementation in Module Five without changing the
service or the controller. This follows the dependency inversion principle and
the practice of programming to an interface rather than to an implementation.

Responsibility placement is the central design decision in this refactor. All
validation is kept in the service rather than spread across the controller and
the model. Some rules require this: rejecting a duplicate ID needs knowledge of
the whole collection, which only the layer that holds the repository has.
Defining the layers first and then assigning each piece of code to the layer it
belongs to keeps the responsibilities separated and the model simple.

The security work maps directly to Outcome 5. Input is validated at the service
boundary (no negative IDs, no out-of-range GPAs, no duplicates), the menu loop
recovers from invalid input instead of failing, and value semantics remove the
manual memory management that leaked in the baseline.

## How to Build and Run

```bash
cd artifact/enhanced
make            # or: g++ -std=c++17 *.cpp -o student_app
./student_app
```

## Acknowledgment of AI Tool Use

In accordance with SNHU's STEM AI Guidelines for Programming Courses, I
acknowledge the use of Claude (Anthropic) as a brainstorming, debugging, and
code-review aid during this enhancement. The tool was used to discuss design
options, explain C++ concepts, review code I wrote, and help organize this
narrative. All code, design decisions, and conclusions are my own work. The AI
tool did not generate the core logic of the implementation, and all content was
reviewed and verified before submission.
