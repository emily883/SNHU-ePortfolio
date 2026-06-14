# Enhancement Two Narrative — Algorithms and Data Structures

**Course:** CS-499 Computer Science Capstone — Southern New Hampshire University
**Student:** Emily Cruz
**Category:** Algorithms and Data Structures (Module Four)
**Artifact:** Student Portal (C++)

## Description and Origin of the Artifact

The artifact is the **Student Portal**, the same C++ console application enhanced
across all three capstone categories. After the Software Design enhancement
(Module Three), the program uses a layered Controller / Service / Repository
architecture, with data stored in memory inside `InMemoryStudentRepository`. This
second enhancement targets the **Algorithms and Data Structures** category and is
limited to that repository layer.

## Justification for Inclusion

In the Module Three version, `findById` performed a **linear search**: it scanned
every element until it found the matching ID, which is O(n). That is the operation
a Student Portal runs most often, so it is a good target for an algorithmic
improvement.

This enhancement replaces the linear search with **binary search** over a vector
that is kept **sorted by ID**, lowering lookup from O(n) to **O(log n)**. Two
deliberate decisions make this an algorithms *and* data structures enhancement
rather than a one-line algorithm swap:

### 1. Data structure choice — why a sorted vector, not a map

A natural reaction is "use a `std::map` or `std::unordered_map`". The sorted
vector is chosen on purpose, with the trade-offs understood:

| Option | Lookup | Notes |
| --- | --- | --- |
| `std::unordered_map` | O(1) average | No ordering; hashing and per-node allocation overhead; **worst case O(n)** on collisions |
| `std::map` (balanced BST) | O(log n) | Ordered, but node-based: pointers scattered in memory, poor cache locality, one allocation per node |
| **Sorted `std::vector` + binary search** | **O(log n)** | Contiguous memory → strong cache locality, low overhead; `getAll()` is already ordered for free |

For this workload the sorted vector is the better fit. The data is small and lives
in contiguous memory, so binary search benefits from cache locality that a
pointer-chasing tree does not get. The portal is also **read-heavy** (searching and
displaying happen far more than adding), and displaying all students now comes out
ordered by ID at no extra cost, because the underlying structure is already sorted.
A hash map would give O(1) lookups but throw away ordering and add overhead the
portal does not need.

### 2. Ordering strategy — the trade-off (Outcome 3)

Binary search requires the vector to be sorted, which raises the real design
question: *when* should the sort happen? This enhancement uses a **lazy (deferred)
sort with a dirty flag**:

- `add()` appends to the end and marks the vector dirty — **O(1) amortized**.
- A private `ensureSorted()` helper runs `std::stable_sort` **once**, only before a
  query, and only if the vector is dirty.

The trade-off is explicit: insertions stay cheap, and the O(n log n) sort cost is
paid a single time on the first query after an insertion. After that, every search
is O(log n). The alternative — sorting on every `add` (eager) — is more expensive
and wasted when students are added in batches before any search. The lazy strategy
fits the portal's "add several, then query" pattern.

`std::stable_sort` is used rather than `std::sort` so that equal keys keep their
insertion order. IDs are unique today (the service rejects duplicates), so
stability is not strictly required for correctness; it is the predictable, safer
choice if the sort key were ever a non-unique field such as name, and the extra
cost is negligible.

### Complexity summary

| Operation | Before (M3) | After (M4) |
| --- | --- | --- |
| `findById` | O(n) linear scan | O(log n) binary search |
| `add` | O(1) | O(1) amortized (+ deferred O(n log n) sort on next query) |
| `getAll` | O(n) copy | O(n) copy, returned already sorted |

## Design Note

The change is contained entirely inside `InMemoryStudentRepository`. The
`IStudentRepository` interface, the `StudentService`, and the `StudentController`
are untouched. The layered architecture from Module Three is what makes this
possible: a faster lookup algorithm can be introduced behind the repository
without affecting the business logic or the user interface.

## Reflection — Course Outcomes

This enhancement supports Outcome 3 (designing and evaluating computing solutions
using algorithmic principles and appropriate trade-offs). The work is the analysis
behind the choices: comparing a sorted vector against tree- and hash-based
containers, selecting the structure that matches a read-heavy, cache-friendly
workload, and choosing a lazy sorting strategy with a stated cost trade-off rather
than sorting blindly on every insert.

Security (Outcome 5) is intentionally out of scope for this category. It is
addressed in the Databases enhancement (Module Five) through parameterized queries
and related input handling.

## How to Build and Run

```bash
cd artifact/enhanced
make            # or: g++ -std=c++17 *.cpp -o student_app
./student_app
```

## Acknowledgment of AI Tool Use

In accordance with SNHU's STEM AI Guidelines for Programming Courses, I
acknowledge the use of Claude (Anthropic) as a brainstorming, debugging, and
code-review aid during this enhancement. The tool was used to discuss algorithm
and data-structure trade-offs, explain C++ concepts, review code I wrote, and help
organize this narrative. All code, design decisions, and conclusions are my own
work. The AI tool did not generate the core logic of the implementation, and all
content was reviewed and verified before submission.
