# Chapter 9 — Error Detection and Handling

Chapter 9 is about the gap between "the code compiles" and "the code is correct." It covers how to *test* code (unit testing, code coverage), how to *think* about errors (preconditions, invariants, happy vs. sad path), and the language tools for *enforcing* expectations — `std::cin` stream-state handling, `assert`, and `static_assert`.

## Lessons

| # | Lesson |
|---|---|
| 9.01 | [Introduction to testing your code](9.01_intro_to_testing/NOTES.md) |
| 9.02 | [Code coverage](9.02_code_coverage/NOTES.md) |
| 9.03 | [Common semantic errors in C++](9.03_common_semantic_errors/NOTES.md) |
| 9.04 | [Detecting and handling errors](9.04_detecting_and_handling_errors/NOTES.md) |
| 9.05 | [`std::cin` and handling invalid input](9.05_cin_invalid_input/NOTES.md) |
| 9.06 | [Assert and `static_assert`](9.06_assert_and_static_assert/NOTES.md) |
| 9.x | [Summary & quiz](9.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the conceptual weight is uneven:

- **9.01 → 9.02** — short, mostly vocabulary (unit test, integration test, statement/branch/loop coverage). Read once and move on.
- **9.04 → 9.05** — the meat of the chapter. 9.04 gives you the vocabulary (precondition, invariant, postcondition, recoverable vs. fatal); 9.05 is where you actually use it, because `std::cin` is the first real-world stream you have to defend against.
- **9.06** — `assert` is for *impossible* states (bugs); error handling is for *possible* states (bad input). Don't conflate them. `static_assert` is a separate tool — compile-time only, always on.
