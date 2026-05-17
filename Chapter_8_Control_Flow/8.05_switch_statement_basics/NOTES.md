# 8.5 — Switch statement basics

> learncpp.com: https://www.learncpp.com/cpp-tutorial/switch-statement-basics/

## Why it matters
A long chain of `else if (x == 1) ... else if (x == 2) ...` is hard to read and the compiler can't help you spot a missing case. `switch` says "dispatch on this **integral** value, here are the labeled cases" — the compiler can warn when you forget one (especially with enums), and a good optimizer compiles it down to a jump table when worthwhile. Use `switch` for discrete-value dispatch; use `if` for ranges and arbitrary booleans.

## Key points
- Shape: `switch (expr) { case k1: ...; break; case k2: ...; break; default: ...; }`. `expr` must be **integral** (int, char, enum). Not strings, not floats.
- Each `case` label must be a **compile-time constant expression**. You can't `case x:` for a runtime `x` — use `if`/`else if`.
- Without a `break`, execution **falls through** to the next case. Deliberate fallthrough is sometimes useful; accidental fallthrough is a classic bug — see 8.6.
- `default:` is the catch-all. Conventionally last, but the language doesn't require it. Including a `default` (or `[[unreachable]]`) makes intent explicit and silences warnings.
- For an `enum class` switch, list every enumerator (or have a `default`). Compilers warn (`-Wswitch`) when you forget one — extremely useful for ensuring exhaustive handling when you later add a new enumerator.

## Code in this folder
- `main.cpp` — `switch` on an int and on an enum. The enum switch is exhaustive (no `default` needed) and demonstrates how a missing case would be caught by the compiler.

## Gotchas
- `case 0..5:` is **not** C++ syntax (it's a GCC extension). Use `case 0: case 1: ... case 5:` or convert to a range check with `if`.
- `switch` only compares equality, never ranges or relational. "If x is between 1 and 9" is an `if`, not a `switch`.
- A `case` label introduces a label, not a scope. To declare a variable inside a case, brace it: `case 1: { int y{ 7 }; ... break; }`. Otherwise other cases can see uninitialized declarations.

## Run
    make 8.05
