# 9.3 — Common semantic errors in C++

> learncpp.com: https://www.learncpp.com/cpp-tutorial/common-semantic-errors-in-c/

## Why it matters
A **syntax error** is "the compiler refused this." A **semantic error** is "the compiler accepted it, but it does the wrong thing." Semantic bugs are the expensive kind — they hide until runtime, sometimes for years. Most of them fall into a small catalog of patterns. Once you've seen them, you spot them faster.

## Key points
The recurring offenders:

- **Conditional / loop terminated with `;`** — `if (x == 0);` followed by a block runs the block unconditionally.
- **Off-by-one** — `<` vs `<=`, `0..n-1` vs `1..n`. Loop coverage (0/1/2 from 9.2) catches these.
- **`=` vs. `==`** — `if (x = 5)` assigns 5 to `x`, evaluates to true, and is a bug. (Modern compilers warn.)
- **Operator-precedence trap** — `(x & 1 == 0)` parses as `x & (1 == 0)`. When in doubt, parenthesize.
- **Integer division** — `5 / 2 == 2`, not `2.5`. Cast one operand to `double`.
- **Signed/unsigned mixing** — `for (unsigned i = v.size() - 1; i >= 0; --i)` never terminates.
- **Uninitialized variable** — reading garbage. Always brace-init: `int x{};`.
- **Wrong type from a function** — e.g. assigning `int` from a `double`-returning function silently truncates.
- **Forgotten `break` in `switch`** — fall-through; legal but rarely intended.
- **Floating-point equality** — `0.1 + 0.2 == 0.3` is `false`. Compare with a tolerance.

## Code in this folder
- `main.cpp` — six common semantic errors, each shown in its **buggy** form (commented or under an `if (false)` block so the program still runs) and then in its **fixed** form, with output that demonstrates the difference.

## Gotchas
- **Compiler warnings catch most of these — turn them on.** `-Wall -Wextra -Wpedantic` is the floor, not the ceiling.
- **A clean compile is not a passed test.** The bugs in this lesson all compile happily.
- **Defensive habits beat after-the-fact debugging**: brace-initialize, parenthesize complex expressions, prefer ranged-for over index loops, prefer `==` only on integer/exact types.

## Run
    make 9.03
