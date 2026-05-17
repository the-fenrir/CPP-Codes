# 4.7 — Introduction to scientific notation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-scientific-notation/

## Why it matters
Floating-point types store numbers *in* scientific notation internally (sign, significand, exponent). Reading and writing it fluently makes the next lesson (4.8) — and every error message about precision — make sense.

## Key points
- Form: `significand × 10^exponent`. In C++ source code: `3.14e2` means `3.14 × 10² = 314`. `1.6e-19` means `1.6 × 10⁻¹⁹`.
- **Normalized** form has exactly one non-zero digit before the decimal point: `5.972e24`, not `59.72e23` or `0.5972e25`.
- **Significant digits** = the digits in the significand. More significant digits = more precision. `3.14` (3 sig figs) is less precise than `3.14159` (6 sig figs).
- Trailing zero rules: `87.0` has 3 sig figs (decimal point makes the trailing zero significant). `2100` is ambiguous; `2100.` (with explicit point) is 4 sig figs.
- This is pure notation — no new C++ syntax beyond the `e` literal form. But internalizing "real numbers are stored as significand + exponent" is the foundation for 4.8.

## Code in this folder
- `main.cpp` — the same value written four different ways, plus a couple of normalized vs. denormalized printouts.

## Gotchas
- `2e3` is a `double` (the literal type), not an `int`. `int x{ 2e3 };` is a narrowing conversion and fails with brace-init.
- `e` is base **10**, not base 2. C++ also has hex float literals (`0x1.8p+1` = `1.5 × 2¹ = 3.0`) but you'll rarely write them by hand.

## Run
    make 4.07
