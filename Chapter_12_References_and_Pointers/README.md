# Chapter 12 — Compound Types: References and Pointers

Chapter 12 introduces the two ways C++ lets one name refer to an object that lives somewhere else: **references** (aliases) and **pointers** (addresses). Almost every function signature, container, and API you'll write later hinges on the distinctions in this chapter — when to copy, when to alias, when to allow null, when to allow rebind.

## Lessons

| # | Lesson |
|---|---|
| 12.01 | [Introduction to compound data types](12.01_intro_to_compound_data_types/NOTES.md) |
| 12.02 | [Value categories (lvalues and rvalues)](12.02_value_categories/NOTES.md) |
| 12.03 | [Lvalue references](12.03_lvalue_references/NOTES.md) |
| 12.04 | [Lvalue references to const](12.04_lvalue_references_to_const/NOTES.md) |
| 12.05 | [Pass by lvalue reference](12.05_pass_by_lvalue_reference/NOTES.md) |
| 12.06 | [Pass by const lvalue reference](12.06_pass_by_const_lvalue_reference/NOTES.md) |
| 12.07 | [Introduction to pointers](12.07_intro_to_pointers/NOTES.md) |
| 12.08 | [Null pointers](12.08_null_pointers/NOTES.md) |
| 12.09 | [Pointers and const](12.09_pointers_and_const/NOTES.md) |
| 12.10 | [Pass by address](12.10_pass_by_address/NOTES.md) |
| 12.11 | [Pass by address (part 2)](12.11_pass_by_address_part2/NOTES.md) |
| 12.12 | [Return by reference and return by address](12.12_return_by_reference_and_address/NOTES.md) |
| 12.13 | [In and out parameters](12.13_in_and_out_parameters/NOTES.md) |
| 12.14 | [Type deduction with pointers, references, and const](12.14_type_deduction_pointers_references_const/NOTES.md) |
| 12.15 | [`std::optional`](12.15_std_optional/NOTES.md) |
| 12.x | [Summary & quiz](12.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear — the chapter is a careful build-up. A few inflection points:

- **12.02 → 12.04** — value categories are the conceptual ground. You can't reason about why `int& r = 5;` fails or why `const int& r = 5;` works until lvalue/rvalue is solid. Don't skim 12.02.
- **12.05 → 12.06** — the pass-by-reference pair. By the end you should reach for `const T&` automatically for any non-trivially-copyable input parameter.
- **12.07 → 12.09** — pointer mechanics. The four `const` combinations in 12.09 trip everyone up; the trick is read right-to-left.
- **12.10 → 12.13** — when *not* to use pointer/reference parameters. Pass-by-address is rarer than newcomers think; prefer references, prefer return-by-value, prefer `std::optional`.
- **12.15** — `std::optional` is the modern answer to "function might not return a value." It replaces most legitimate uses of nullable out-pointers and sentinel return values.
