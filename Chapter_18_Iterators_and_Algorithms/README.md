# Chapter 18 — Iterators and Algorithms

Chapter 18 is short and pragmatic: hand-roll a sort to see why the standard library exists, learn the iterator abstraction that makes generic algorithms possible, then use `<algorithm>` to replace your hand-rolled loops. Closes with how to actually measure whether one version is faster than another.

## Lessons

| # | Lesson |
|---|---|
| 18.01 | [Sorting an array using selection sort](18.01_selection_sort/NOTES.md) |
| 18.02 | [Introduction to iterators](18.02_intro_to_iterators/NOTES.md) |
| 18.03 | [Introduction to standard library algorithms](18.03_intro_to_stdlib_algorithms/NOTES.md) |
| 18.04 | [Timing your code](18.04_timing_your_code/NOTES.md) |
| 18.x | [Summary & quiz](18.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The progression is deliberate:

- **18.01 → 18.03** — you sort by hand, then learn the abstraction (iterators) that lets you stop sorting by hand, then use it (`std::sort`, `std::find`, `std::for_each`). Reading 18.03 before 18.02 will leave the iterator parameters feeling magical.
- **18.04** — keep this one in your back pocket. It's the only honest answer to "is version A faster than version B?" you'll get in this book.
