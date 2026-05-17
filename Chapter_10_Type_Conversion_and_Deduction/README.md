# Chapter 10 — Type Conversion, Type Aliases, and Type Deduction

Chapter 10 nails down what actually happens when one type meets another: implicit conversions the compiler inserts for you, promotions vs. narrowing, the arithmetic rules that govern mixed-type expressions, explicit casts, and the two ergonomic tools — type aliases and `auto` — that let you name (or stop naming) types.

## Lessons

| # | Lesson |
|---|---|
| 10.01 | [Implicit type conversion](10.01_implicit_type_conversion/NOTES.md) |
| 10.02 | [Floating-point and integral promotion](10.02_numeric_promotion/NOTES.md) |
| 10.03 | [Numeric conversions](10.03_numeric_conversions/NOTES.md) |
| 10.04 | [Narrowing conversions, list initialization & constexpr initializers](10.04_narrowing_conversions/NOTES.md) |
| 10.05 | [Arithmetic conversions](10.05_arithmetic_conversions/NOTES.md) |
| 10.06 | [Explicit type conversion (casting) and `static_cast`](10.06_explicit_static_cast/NOTES.md) |
| 10.07 | [Typedefs and type aliases](10.07_typedefs_and_type_aliases/NOTES.md) |
| 10.08 | [Type deduction for objects using `auto`](10.08_auto_type_deduction_objects/NOTES.md) |
| 10.09 | [Type deduction for functions](10.09_type_deduction_functions/NOTES.md) |
| 10.x  | [Summary & quiz](10.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The chapter builds a vocabulary you'll use forever:

- **10.01 → 10.05** are one continuous story: what the compiler does silently. Promotion (10.02) is safe; numeric conversion (10.03) is not; narrowing (10.04) is the diagnostic; arithmetic conversion (10.05) is what makes `int + double` legal.
- **10.06** is the manual override — `static_cast` to say "I know, do it anyway."
- **10.07 → 10.09** shift gears: instead of *converting* types, these are about *naming* or *omitting* them. Type aliases are documentation; `auto` is type deduction. Read them as a pair.
