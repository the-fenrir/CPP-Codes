# 4.8 — Floating point numbers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/floating-point-numbers/

## Why it matters
Floats are how C++ represents real numbers — but they're a **finite, base-2** approximation of the real number line. Most decimal fractions you write (`0.1`, `0.2`, `0.3`) cannot be represented exactly. That's not a bug; that's IEEE 754, and every floating-point bug you'll ever hit comes from forgetting it.

## Key points
- Three types: `float` (4 bytes, ~6–9 decimal sig figs), `double` (8 bytes, ~15–18 sig figs), `long double` (≥ 8 bytes, platform-dependent — frequently the same as `double` on Windows, 80-bit extended on Linux x86).
- **Default to `double`.** Use `float` only when storage matters and the loss of precision is acceptable. `long double` is portability sand.
- A floating-point **literal** is a `double` by default. `3.14f` is a `float`; `3.14L` is a `long double`.
- `std::setprecision(n)` from `<iomanip>` controls how many digits `std::cout` prints. It's **sticky** — affects every subsequent floating-point output until changed.
- **Rounding error is the rule, not the exception**: `0.1 + 0.2 != 0.3` exactly. Never compare floating-point values with `==`; compare with a tolerance, or restructure to avoid the comparison.
- IEEE 754 also produces special values: `Inf` (e.g. `1.0 / 0.0`), `-Inf`, `NaN` (e.g. `0.0 / 0.0`, `std::sqrt(-1.0)`). `NaN != NaN` is `true` — use `std::isnan` to test.

## Code in this folder
- `main.cpp` — type sizes, `setprecision` showing hidden digits, the classic `0.1 + 0.2` bug, and an Inf/NaN demo.

## Gotchas
- `setprecision` without `std::fixed` controls **total** significant digits. With `std::fixed`, it controls digits **after the decimal point**. Different defaults catch everyone once.
- Dividing an integer by zero is undefined behavior. Dividing a `double` by `0.0` is well-defined and produces `±Inf` (with an FP exception flag set). Different rules, same-looking code.

## Run
    make 4.08
