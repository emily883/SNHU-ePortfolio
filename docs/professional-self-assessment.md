# Professional Self-Assessment

**Emily Cruz Gutierrez** — CS-499 Computer Science Capstone, Southern New Hampshire University
**June 21, 2026**

## Introduction

I am a software developer who became self-taught during the pandemic and has since pursued growth beyond routine development toward rigorous, high-impact engineering. What distinguishes my work is not that I go deep for its own sake, but *why* I go deep: I anchor my conclusions in solid evidence and actively guard against my own preferences steering the direction of an analysis. I treat "it works" as the beginning of an evaluation, not the end of one — asking why a design holds, where it could break, and what assumptions it depends on.

This ePortfolio centers on a single artifact, a C++ Student Portal, which I enhanced across all three program areas: software design and engineering, algorithms and data structures, and databases. Using one artifact was deliberate — it let each enhancement build on the last and let me show that the same engineering judgment carried through every layer. The sections below introduce the broader skills the program developed in me, with this artifact and my professional work as evidence.

## Collaborating in a Team Environment

I have worked primarily as an independent developer, so my strength in this outcome is *collaboration-readiness*: building work others can join and act on, rather than a history of teams. My layered architecture coordinates contributors through explicit interface contracts — the `IStudentRepository` interface is the only surface two developers must agree on, which lets each work inside a layer without breaking the others. I use a disciplined version-control workflow with a separate branch per stage of work, and I write documentation for a reader who does not share my current context — beginning with my own future self as the first maintainer. If code is clear enough that I can return to it months later and act without rediscovering it, it is clear enough for a teammate to do the same. The code review in this portfolio is itself the collaborative artifact of this competency.

## Communicating With Stakeholders

When I explain a technical decision to someone who does not live inside the code, I follow a deliberate structure: I establish the current context first, then state what was decided, then justify the choice against that context with evidence. This keeps my reasoning anchored to the situation rather than to opinion. My enhancement narratives apply this to trade-offs a non-specialist can follow — why a sorted vector rather than a hash map, why salted hashing is only a starting point — and adapt the level of detail to the reader. The code review is the oral and visual form of the same skill, and this self-assessment its written form.

## Data Structures and Algorithms

I choose data structures and algorithms by context, not by trend. A student system for a small school does not need heavy machinery, and adding it would be over-engineering; I replaced linear search with binary search over a sorted vector, an O(log n) lookup that is both fast and exact. My criterion for implementing something myself versus relying on an established library is explicit: I hand-roll when a problem is simple, well understood, and not security-critical, where controlling the implementation adds clarity; I defer to vetted, proven implementations when a problem is security-critical, cryptographic, or already solved well — and I let evidence, not preference, decide which. In a system of record, I optimize for responsiveness *within* exact correctness; speed is never traded against returning the right result.

## Software Engineering and Database

My core engineering skill is diagnostic: I can read a tangled monolith and see the distinct responsibilities fused inside it — business logic, data handling, and search bundled into one file — and separate them into a clean Controller / Service / Repository design. I proved the separation was real, not cosmetic, by replacing the in-memory store with SQLite persistence without changing a line of the controller or service layers. I also corrected root-cause defects in the baseline, including an out-of-bounds off-by-one and a short-circuiting search bug. I build for adaptability to change: a system that absorbs new requirements without breaking.

## Security Mindset

A security mindset, to me, begins with honesty about a system's limits, because false assurance is itself a vulnerability — overstating what a system protects makes it more dangerous, since people trust it and skip the protections it still needs. I implemented parameterized queries to prevent SQL injection, input validation at the application boundary, and role-based access control at the service layer, with salted password hashing — and I stated plainly that salted hashing is a stepping stone, not production-grade, and that a real system needs bcrypt or Argon2. Naming what a system does *not* protect is what lets the next engineer close the gap, and it reflects accountability for the real risk posture rather than a marketed one.

## Summary

Taken together, this portfolio is one artifact carried through three enhancements that each demonstrate the same discipline: decisions grounded in evidence and context, honest about their limits, and built to withstand change. That discipline also defines where I am going. I want to research methods to mitigate software fragility and recover robustness in modern systems — not a return to older software, but a reduced, well-founded set of robustness practices distilled from the sprawling catalog of patterns in use today, and validated carefully so the work does not simply become one more entry in the list it set out to simplify. The capstone is the seed of that direction; the research is where I intend to take it.

---

*Acknowledgment of AI use:* In accordance with SNHU's STEM AI guidelines, I used an AI assistant to help organize and structure ideas I articulated myself and to polish wording in my own voice. The reflections, decisions, technical analysis, and research direction in this assessment are my own.
