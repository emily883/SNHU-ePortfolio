# Emily Cruz — Computer Science Capstone ePortfolio

Welcome. This ePortfolio is the capstone (CS-499) work for my B.S. in Computer
Science at Southern New Hampshire University. It centers on a single artifact, the
**Student Portal** (C++), which I enhanced across the three core areas of the
program: software design and engineering, algorithms and data structures, and
databases.

## Professional Self-Assessment

My professional self-assessment introduces who I am as an engineer, the skills this
program developed, and how the work below demonstrates them. It is the best place
to start.

➡️ [Read the Professional Self-Assessment](professional-self-assessment.md)

## The artifact: Student Portal

The Student Portal began as instructor-provided starter code — a small,
single-file student information system with several intentional defects. Across the
capstone I rebuilt it into a layered, secure, database-backed application while
preserving the same architecture throughout.

| Version | What it shows | Where |
| --- | --- | --- |
| **Original** | The unmodified baseline (for before/after comparison) | [`artifact/original/`](https://github.com/emily883/SNHU-ePortfolio/tree/module5/artifact/original) |
| **Enhanced** | The full enhanced application | [`artifact/enhanced/`](https://github.com/emily883/SNHU-ePortfolio/tree/module5/artifact/enhanced) |

## Code Review

My code review walks through the original artifact, analyzes it for weaknesses and
maintainability, and explains the enhancements I planned across the three
categories. It is the collaborative walkthrough of how the project evolved.

## Enhancement One — Software Design and Engineering

I refactored the monolithic baseline into a layered **Controller / Service /
Repository** architecture with dependency injection, encapsulation, input
validation, and memory-safe value semantics. This is the foundation that made the
later enhancements possible without rewrites.

➡️ [Read the Enhancement One narrative](https://github.com/emily883/SNHU-ePortfolio/blob/module5/artifact/enhanced/module-three-narrative.md)

## Enhancement Two — Algorithms and Data Structures

I replaced the linear search with **binary search** over a vector kept sorted with
a lazy `stable_sort`, taking lookups from O(n) to O(log n), and documented the
data-structure trade-offs (sorted vector vs. `std::map` / `unordered_map`).

➡️ [Read the Enhancement Two narrative](https://github.com/emily883/SNHU-ePortfolio/blob/module5/artifact/enhanced/module-four-narrative.md)

## Enhancement Three — Databases

I added **SQLite persistence** with parameterized queries, full CRUD,
criteria-based search and reporting, and **role-based access control** with salted,
hashed passwords — a security-focused capstone to the project.

➡️ [Read the Enhancement Three narrative](https://github.com/emily883/SNHU-ePortfolio/blob/module5/artifact/enhanced/module-five-narrative.md)

## Contact

- **GitHub:** [github.com/emily883](https://github.com/emily883)
- **LinkedIn:** [linkedin.com/in/emily-fullstack](https://www.linkedin.com/in/emily-fullstack/)
- **Email:** [emily.cruzgutierrez@snhu.edu](mailto:emily.cruzgutierrez@snhu.edu)

---

*Repository:* [github.com/emily883/SNHU-ePortfolio](https://github.com/emily883/SNHU-ePortfolio)
