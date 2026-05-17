# Chapter 7 — Scope, Duration, and Linkage

Chapter 7 nails down three orthogonal properties every C++ identifier has: **scope** (where the name is visible), **duration** (when storage lives), and **linkage** (whether the same name refers to the same entity across translation units). Getting these wrong is the source of most "works in one file, breaks when split into two" bugs.

## Lessons

| # | Lesson |
|---|---|
| 7.01 | [Compound statements (blocks)](7.01_compound_statements/NOTES.md) |
| 7.02 | [User-defined namespaces and the scope resolution operator](7.02_user_defined_namespaces/NOTES.md) |
| 7.03 | [Local variables](7.03_local_variables/NOTES.md) |
| 7.04 | [Introduction to global variables](7.04_intro_to_global_variables/NOTES.md) |
| 7.05 | [Variable shadowing (name hiding)](7.05_variable_shadowing/NOTES.md) |
| 7.06 | [Internal linkage](7.06_internal_linkage/NOTES.md) |
| 7.07 | [External linkage and variable forward declarations](7.07_external_linkage/NOTES.md) |
| 7.08 | [Why (non-const) global variables are evil](7.08_why_non_const_globals_are_evil/NOTES.md) |
| 7.09 | [Inline functions and variables](7.09_inline_functions_and_variables/NOTES.md) |
| 7.10 | [Sharing global constants across multiple files](7.10_sharing_global_constants/NOTES.md) |
| 7.11 | [Static local variables](7.11_static_local_variables/NOTES.md) |
| 7.12 | [Scope, duration, and linkage summary](7.12_scope_duration_linkage_summary/NOTES.md) |
| 7.13 | [Using declarations and using directives](7.13_using_declarations_and_directives/NOTES.md) |
| 7.14 | [Unnamed and inline namespaces](7.14_unnamed_and_inline_namespaces/NOTES.md) |
| 7.x  | [Summary & quiz](7.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear, but the three concepts only click together at **7.12**. Mileposts:

- **7.01–7.03** — scope mechanics. Easy, but pay attention to lifetime in 7.03; it's the foundation for static locals in 7.11.
- **7.06 → 7.07** — internal vs. external linkage. These are the lessons that finally explain why `static` at file scope and `extern` exist. Both are multi-file folders; read the actual `.cpp` files side by side.
- **7.09 → 7.10** — `inline` was redefined in C++17 to mean "this entity may be defined in multiple TUs, the linker picks one." 7.10 is the canonical use: header-only global constants.
- **7.08** — the *why*. Read after 7.07 so the recommendation has bite.
- **7.13 → 7.14** — namespace usage. `using namespace` is fine in `.cpp` scope, dangerous at file scope, lethal in a header. Unnamed namespaces are the modern alternative to file-scope `static`.
