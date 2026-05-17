# Chapter 13 — Compound Types: Enums and Structs

Chapter 13 builds the first program-defined types in C++: enumerations (named integer constants with a type) and structs (aggregates that bundle named members). By the end you can model small fixed sets of states, group related data into named records, pass and return them efficiently, and parameterize them over a type with class templates — the direct setup for Chapter 14's move from struct to class.

## Lessons

| # | Lesson |
|---|---|
| 13.01 | [Introduction to program-defined (user-defined) types](13.01_program_defined_types/NOTES.md) |
| 13.02 | [Unscoped enumerations](13.02_unscoped_enumerations/NOTES.md) |
| 13.03 | [Unscoped enumerator integral conversions](13.03_unscoped_enum_integral_conversions/NOTES.md) |
| 13.04 | [Converting an enumeration to and from a string](13.04_enum_to_from_string/NOTES.md) |
| 13.05 | [Introduction to overloading the I/O operators](13.05_overloading_io_operators/NOTES.md) |
| 13.06 | [Scoped enumerations (`enum class`)](13.06_scoped_enumerations/NOTES.md) |
| 13.07 | [Introduction to structs, members, and member selection](13.07_intro_to_structs/NOTES.md) |
| 13.08 | [Struct aggregate initialization](13.08_struct_aggregate_initialization/NOTES.md) |
| 13.09 | [Default member initialization](13.09_default_member_initialization/NOTES.md) |
| 13.10 | [Passing and returning structs](13.10_passing_and_returning_structs/NOTES.md) |
| 13.11 | [Struct miscellany](13.11_struct_miscellany/NOTES.md) |
| 13.12 | [Member selection with pointers and references](13.12_member_selection_with_pointers_refs/NOTES.md) |
| 13.13 | [Class templates](13.13_class_templates/NOTES.md) |
| 13.14 | [Class template argument deduction (CTAD) and deduction guides](13.14_ctad_and_deduction_guides/NOTES.md) |
| 13.15 | [Alias templates](13.15_alias_templates/NOTES.md) |
| 13.x  | [Summary & quiz](13.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear — the chapter is in two halves that don't overlap until the quiz brings them together.

- **13.01 → 13.06** — enums. The cliff is 13.03 (implicit-to-int conversion *yes*, int-to-enum *no without a cast*) and 13.06 (scoped enums fix both directions). Read 13.04 and 13.05 as a pair: `operator<<` overload is *the* idiomatic way to print an enum.
- **13.07 → 13.12** — structs. 13.08 (aggregate init) and 13.09 (default member initializers) interlock; understand both before reading 13.10. 13.10 introduces a `Fraction` struct that comes back in the Chapter 14 quiz — pay attention to the signatures.
- **13.13 → 13.15** — class templates. New syntax, same idea as function templates from chapter 11. CTAD (13.14) is mostly a quality-of-life feature; the deduction-guide rule for C++17 is the one footgun.
