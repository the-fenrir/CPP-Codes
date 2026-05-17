# Chapter 6 — Operators

Chapter 6 covers the everyday operators: arithmetic, increment/decrement, comma, conditional, relational, and logical. The throughline is precedence/associativity vs. *order of evaluation* — two distinct concepts that get mixed up constantly. Get this chapter right and most "why is my expression doing that?" bugs disappear.

## Lessons

| # | Lesson |
|---|---|
| 6.01 | [Operator precedence and associativity](6.01_precedence_and_associativity/NOTES.md) |
| 6.02 | [Arithmetic operators](6.02_arithmetic_operators/NOTES.md) |
| 6.03 | [Remainder and exponentiation](6.03_remainder_and_exponentiation/NOTES.md) |
| 6.04 | [Increment/decrement, and side effects](6.04_increment_decrement_side_effects/NOTES.md) |
| 6.05 | [The comma operator](6.05_comma_operator/NOTES.md) |
| 6.06 | [The conditional operator](6.06_conditional_operator/NOTES.md) |
| 6.07 | [Relational operators and floating-point comparisons](6.07_relational_operators_and_floats/NOTES.md) |
| 6.08 | [Logical operators](6.08_logical_operators/NOTES.md) |
| 6.x | [Summary & quiz](6.x_summary_and_quiz/NOTES.md) |

## Suggested order

Linear. Two pairings worth flagging:

- **6.01 + 6.04** — precedence and side effects are the foundation for *why* `i = i++ + ++i;` is undefined. Read 6.04 with 6.01 fresh in mind.
- **6.07 + 6.08** — relational results feed straight into logical compositions. Once you have both, you can write any condition cleanly.

The conditional operator (6.06) is the most over-used operator in the chapter — read it as much for *when not to reach for it* as for syntax.
