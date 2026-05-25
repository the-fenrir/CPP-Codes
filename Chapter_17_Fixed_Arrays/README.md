# Chapter 17 — Fixed-size arrays: std::array and C-style arrays

Chapter 17 covers the *fixed-size* end of the array spectrum: `std::array` (the modern, type-safe choice) and C-style arrays (the C inheritance you still have to read in real code). You'll learn how length and indexing are encoded in the type, how arrays behave when passed/returned, the C-style array decay rule that breaks everything novices assume, and how multidimensional arrays work in both flavors.

## Lessons

| # | Lesson |
|---|---|
| 17.01 | [Introduction to `std::array`](17.01_intro_to_stdarray/NOTES.md) |
| 17.02 | [`std::array` length and indexing](17.02_stdarray_length_and_indexing/NOTES.md) |
| 17.03 | [Passing and returning `std::array`](17.03_passing_and_returning_stdarray/NOTES.md) |
| 17.04 | [`std::array` of class types, and brace elision](17.04_stdarray_of_class_types_and_brace_elision/NOTES.md) |
| 17.05 | [Arrays of references via `std::reference_wrapper`](17.05_arrays_of_references_via_reference_wrapper/NOTES.md) |
| 17.06 | [`std::array` and enumerations](17.06_stdarray_and_enumerations/NOTES.md) |
| 17.07 | [Introduction to C-style arrays](17.07_intro_to_c_style_arrays/NOTES.md) |
| 17.08 | [C-style array decay](17.08_c_style_array_decay/NOTES.md) |
| 17.09 | [Pointer arithmetic and subscripting](17.09_pointer_arithmetic_and_subscripting/NOTES.md) |
| 17.10 | [C-style strings](17.10_c_style_strings/NOTES.md) |
| 17.11 | [C-style string symbolic constants](17.11_c_style_string_symbolic_constants/NOTES.md) |
| 17.12 | [Multidimensional C-style arrays](17.12_multidimensional_c_style_arrays/NOTES.md) |
| 17.13 | [Multidimensional `std::array`](17.13_multidimensional_stdarray/NOTES.md) |
| 17.x | [Summary & quiz](17.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but with a few pivot points:

- **17.01 → 17.03** — `std::array` basics + how it survives function boundaries. 17.03 is the lesson where `std::array<int, N>` "feels different" from a `std::vector` clicks.
- **17.04 → 17.06** — practical patterns: arrays of class objects, holding references, and using enums as compile-time indices into parallel arrays.
- **17.07 → 17.09** — C-style arrays. Read 17.08 (decay) twice; it's the single rule that explains 80% of legacy-array bugs.
- **17.10 → 17.11** — C-style strings exist because the language still emits them from string literals. Know enough to migrate them to `std::string_view`.
- **17.12 → 17.13** — multidimensional arrays. Note how C-style nesting is special-cased by the compiler in ways `std::array<std::array<...>>` is not, hence C++23's `std::mdspan` and the like.
