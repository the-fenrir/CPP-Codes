# Chapter 23 — Object Relationships

Real systems are built out of objects that *refer* to other objects. Chapter 23 names the four relationship strengths — **composition**, **aggregation**, **association**, **dependency** — gives you the rules of thumb for picking between them, and then applies them to two concrete designs: a hand-rolled container class and a class that accepts `std::initializer_list` for brace-init.

## Lessons

| # | Lesson |
|---|---|
| 23.01 | [Object relationships](23.01_object_relationships/NOTES.md) |
| 23.02 | [Composition](23.02_composition/NOTES.md) |
| 23.03 | [Aggregation](23.03_aggregation/NOTES.md) |
| 23.04 | [Association](23.04_association/NOTES.md) |
| 23.05 | [Dependencies](23.05_dependencies/NOTES.md) |
| 23.06 | [Container classes](23.06_container_classes/NOTES.md) |
| 23.07 | [`std::initializer_list`](23.07_initializer_list/NOTES.md) |
| 23.x  | [Summary & quiz](23.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The first five lessons form a single spectrum from strongest coupling (composition) to weakest (dependency); reading them out of order loses the contrast that makes the distinctions worth memorising.

- **23.02 → 23.05** — same mental model in four flavours. The questions to ask are always: *who controls lifetime?*, *can the part belong to multiple wholes?*, *does the part know about the whole?* The answers are what separate the four relationships.
- **23.06 → 23.07** — `IntArray`-as-container is the running example; `std::initializer_list` then plugs straight into that container so brace-init `IntArray a{ 1, 2, 3 };` does the obvious thing. Read them as a pair.
- **23.x** — the quiz is *entirely* classification ("is this composition or aggregation?"). If 23.02–23.05 didn't stick, this is where you find out.
