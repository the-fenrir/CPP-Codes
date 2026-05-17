# 6.7 — Relational operators and floating-point comparisons

> learncpp.com: https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/

## Why it matters
The six comparisons (`==`, `!=`, `<`, `<=`, `>`, `>=`) are easy on integers. On `double`/`float` they're a trap: `0.1 + 0.2 == 0.3` is **false** because the values can't be represented exactly. Almost every "my math is off in the last digit" bug traces back to this. Knowing when to compare with tolerance — and how — is the difference between "works" and "works on my machine."

## Key points
- All six return `bool`. Use directly in conditions: `if (x > 0)`, not `if ((x > 0) == true)`.
- **Integers**: `==` and `!=` are fine. Watch signed/unsigned mixing — comparisons promote.
- **Floats / doubles**: `==` and `!=` are almost always wrong on computed values. Two values that *should* be equal often differ in the last few ULPs.
- **Absolute epsilon** (`|a - b| < eps`): simple, but only correct when the magnitude is known. Useless near 0 of large values, useless for "is `1e9 + 0.5` close to `1e9`?"
- **Relative epsilon** (`|a - b| < eps * max(|a|, |b|)`): scales with magnitude. Knuth's approach. Breaks near zero (both sides ~0 → false negatives).
- **Hybrid (recommended)**: `|a - b| < absEps || |a - b| < relEps * max(|a|, |b|)`. Handles both ends.
- `NaN` is never equal to anything — even itself. `nan == nan` is false. `x != x` is the classic NaN test.

## Code in this folder
- `main.cpp` — `0.1 + 0.2 != 0.3`, three approxEqual implementations, NaN's quirks.

## Gotchas
- `if (b == true)` is noise. Just `if (b)`. Same for `if (b == false)` → `if (!b)`.
- Don't compare floats with `==` even when "obviously equal" if either side came out of a calculation.
- Choosing `eps`: there's no universal value. For most everyday doubles, `1e-9` for absolute and `1e-8` for relative is a reasonable start. *Test it against your inputs.*

## Run
    make 6.07
