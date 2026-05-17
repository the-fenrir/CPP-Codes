# Chapter 4 — Fundamental Data Types

Chapter 4 catalogues the built-in types: integers (signed, unsigned, fixed-width), floating point, `bool`, `char`, plus `void` and `std::nullptr_t`. By the end you can pick the right type for a value, reason about size/range/precision, do basic conditional logic with `if`, and convert between types deliberately with `static_cast`.

## Lessons

| # | Lesson |
|---|---|
| 4.01 | [Introduction to fundamental data types](4.01_intro_to_fundamental_data_types/NOTES.md) |
| 4.02 | [Void](4.02_void/NOTES.md) |
| 4.03 | [Object sizes and the `sizeof` operator](4.03_object_sizes_and_sizeof/NOTES.md) |
| 4.04 | [Signed integers](4.04_signed_integers/NOTES.md) |
| 4.05 | [Unsigned integers, and why to avoid them](4.05_unsigned_integers/NOTES.md) |
| 4.06 | [Fixed-width integers and `size_t`](4.06_fixed_width_integers_and_size_t/NOTES.md) |
| 4.07 | [Introduction to scientific notation](4.07_scientific_notation/NOTES.md) |
| 4.08 | [Floating point numbers](4.08_floating_point_numbers/NOTES.md) |
| 4.09 | [Boolean values](4.09_boolean_values/NOTES.md) |
| 4.10 | [Introduction to if statements](4.10_if_statements/NOTES.md) |
| 4.11 | [Chars](4.11_chars/NOTES.md) |
| 4.12 | [Introduction to type conversion and `static_cast`](4.12_type_conversion_and_static_cast/NOTES.md) |
| 4.x  | [Summary & quiz](4.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear — types build on each other. Worth slowing down on:

- **4.04 → 4.05** — signed overflow is UB, unsigned wraps. Read them as a pair so you internalize *why* the chapter recommends signed by default.
- **4.06** — `std::int8_t` and `std::uint8_t` aliasing `signed char`/`unsigned char` is the classic gotcha; you'll see it again any time you print a small fixed-width integer.
- **4.08** — floating point precision and rounding error. Don't memorize the digit counts; understand that `0.1` is not exactly `0.1` and that equality comparison on floats is almost always wrong.
- **4.12** — brace-init refusing narrowing conversions is *the* feature that makes chapter 1's "always use `int x{ 5 };`" advice worth following.
