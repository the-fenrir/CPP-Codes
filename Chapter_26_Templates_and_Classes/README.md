# Chapter 26 — Templates and Classes

Chapter 26 finishes the templates story started in chapter 11 and revisited in 15.5: class templates with non-type parameters, specializing individual functions, specializing whole classes (fully or partially), and the pointer-specialization pattern that bridges templates and ownership semantics.

## Lessons

| # | Lesson |
|---|---|
| 26.01 | [Template classes](26.01_template_classes/NOTES.md) |
| 26.02 | [Template non-type parameters](26.02_template_non_type_parameters/NOTES.md) |
| 26.03 | [Function template specialization](26.03_function_template_specialization/NOTES.md) |
| 26.04 | [Class template specialization](26.04_class_template_specialization/NOTES.md) |
| 26.05 | [Partial template specialization](26.05_partial_template_specialization/NOTES.md) |
| 26.06 | [Partial template specialization for pointers](26.06_partial_template_specialization_for_pointers/NOTES.md) |
| 26.x | [Summary & quiz](26.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. The chapter is one continuous thread — each lesson narrows the previous one:

- **26.01–26.02** — class templates plus NTTPs. If 15.5 already made sense, this is the natural extension; the NTTP idea (`std::array<int, 5>`) is the conceptual unlock.
- **26.03 → 26.04** — function vs. class specialization. Read them as a pair: the function form is the one you'll *avoid* in favor of overloads, the class form is the one you'll actually use.
- **26.05 → 26.06** — partial specialization, capped off with the canonical pointer-specialization example. 26.06 is where ownership semantics start to bite — note the three escape hatches it lays out.
