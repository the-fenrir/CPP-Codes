# Chapter 5 — Constants and Strings

Chapter 5 covers how to lock values down (`const`, `constexpr`), how the compiler reasons about constant expressions, and the two string types you'll actually reach for in modern C++: `std::string` (owns its data) and `std::string_view` (borrows it). By the end you can tell a runtime constant from a compile-time one, pick the right string type for a parameter, and avoid the classic dangling `string_view` footgun.

## Lessons

| # | Lesson |
|---|---|
| 5.01 | [Constant variables (named constants)](5.01_constant_variables/NOTES.md) |
| 5.02 | [Literals](5.02_literals/NOTES.md) |
| 5.03 | [Numeral systems (decimal, binary, hex, octal)](5.03_numeral_systems/NOTES.md) |
| 5.04 | [The as-if rule and compile-time optimization](5.04_as_if_rule/NOTES.md) |
| 5.05 | [Constant expressions](5.05_constant_expressions/NOTES.md) |
| 5.06 | [Constexpr variables](5.06_constexpr_variables/NOTES.md) |
| 5.07 | [Introduction to `std::string`](5.07_intro_to_std_string/NOTES.md) |
| 5.08 | [Introduction to `std::string_view`](5.08_intro_to_std_string_view/NOTES.md) |
| 5.09 | [`std::string_view` (part 2)](5.09_std_string_view_part_2/NOTES.md) |
| 5.x | [Summary & quiz](5.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The chapter has two natural halves:

- **5.01 → 5.06 — constants.** Read `const` (5.01), then literals (5.02–5.03) so you can recognize what's already a compile-time value, then the `constexpr` story (5.04–5.06) end-to-end. The as-if rule (5.04) is the conceptual glue: it explains *why* `constexpr` even exists.
- **5.07 → 5.09 — strings.** `std::string` first (owning, safe, slightly expensive), then `std::string_view` (cheap, but dangling is on you). Don't skip 5.09 — most `string_view` bugs come from the lifetime rules covered there, not the basics in 5.08.
