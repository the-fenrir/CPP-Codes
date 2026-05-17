# 10.5 — Arithmetic conversions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/arithmetic-conversions/

## Why it matters
Binary arithmetic operators (`+ - * / %`, comparisons, bitwise) require both operands to be the same type. When they aren't, the compiler picks a **common type** by following the *usual arithmetic conversions* — a fixed priority ladder. Knowing the ladder explains a category of bugs whose root cause is "I wrote `int / int` and got an `int`."

## Key points
- Priority ladder (highest first):
  1. `long double`
  2. `double`
  3. `float`
  4. `unsigned long long`
  5. `long long`
  6. `unsigned long`
  7. `long`
  8. `unsigned int`
  9. `int`
- If either operand is on the ladder, **both are converted to the higher rank**. If both are below `int`, both are *promoted to `int`* first (10.02).
- Special case: integer / integer = integer. `5 / 2 == 2`, not `2.5`. To get the FP answer, at least one operand must be FP: `5 / 2.0` or `static_cast<double>(5) / 2`.
- Mixing signed and unsigned at the same rank converts the **signed** value to unsigned. That's how `-1 < 1u` becomes `false`.

## Code in this folder
- `main.cpp` — works through the most-asked-about cases: integer division, mixed FP, signed-vs-unsigned comparison.

## Gotchas
- `average = (a + b) / 2;` where `a, b` are `int` — division is integer division. Cast one side to `double` or use `2.0`.
- `if (someInt < someUnsigned)` — the int converts to unsigned. Negative `someInt` becomes a giant positive number. Compilers warn for this; listen.
- Watch out for `auto`: `auto avg = sum / count;` inherits whatever the conversion produced. `auto` doesn't fix the rules.

## Run
    make 10.05
