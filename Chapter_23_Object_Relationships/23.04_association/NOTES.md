# 23.4 — Association

> learncpp.com: https://www.learncpp.com/cpp-tutorial/association/

## Why it matters
Aggregation says "part-of" — a `Department` has `Teacher`s. Association drops even that. A `Doctor` and a `Patient` are *peers*: neither is a part of the other, neither owns the other, but they need to know about each other. Most cross-object references in real systems are associations, not aggregations — and conflating them is how design diagrams turn into spaghetti.

## Key points
- Association = **uses-a, ongoing, between peers**. Two otherwise-unrelated classes that need a long-lived link to each other.
- Differs from aggregation in semantics, not always in code: aggregation is part/whole, association is peer/peer. Both store pointers/references; both leave lifetime alone.
- Differs from composition in everything: not part-of, not owning, not exclusive.
- Can be **unidirectional** (Doctor knows Patient, Patient doesn't know Doctor) or **bidirectional** (both know each other). Prefer unidirectional — bidirectional links must be kept in sync and are a constant source of bugs.
- **Direct vs. indirect** association: store a pointer/reference (direct), or store an ID + look it up (indirect). Indirect is slower per access but resilient to lifetime issues and works across address spaces (db rows, network).
- **Reflexive** association: a class associated with another instance of itself — `Course` lists prerequisite `Course`s.

## Code in this folder
- `main.cpp` — `Doctor` and `Patient`, bidirectionally associated by pointer. Each can list the other; neither owns the other; their lifetimes are independent.

## Gotchas
- Bidirectional associations need an `addPatient`/`addDoctor` pair that *both* update. Forget one side and the graph silently lies.
- A direct association by pointer dangles the instant the pointee dies. If you can't guarantee lifetime ordering, use indirect association (IDs) instead.
- Don't reach for friendship just to wire up an association. Provide narrow add/remove member functions on each side.

## Run
    make 23.04
