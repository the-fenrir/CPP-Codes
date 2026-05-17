# 10.3 — Numeric conversions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/numeric-conversions/

## Why it matters
Promotion (10.02) handles the safe widenings. **Numeric conversion** is everything else between numeric types: signed↔unsigned, wider↔narrower, integer↔floating. Some preserve value, some don't. The compiler will do most of them silently — knowing which ones lose information is what stops you from being surprised in production.

## Key points
- Five categories of numeric conversion:
  1. Integral → different integer type (e.g. `int → short`, `int → unsigned`).
  2. Floating-point → different FP type (e.g. `double → float`).
  3. Floating-point → integer (`double → int`): **truncates** toward zero.
  4. Integer → floating-point (`int → double`): exact for small values; large integers may not be exactly representable as `double`.
  5. Integer or FP → `bool`: zero becomes `false`, anything else `true`.
- A conversion is **value-preserving** only when every source value is representable in the destination type. Otherwise it's **lossy**.
- "Lossy" doesn't mean "compile error." Outside list initialization, it usually just warns.
- Signed → unsigned of a negative value wraps modulo 2^N. Yes, defined behavior. No, still not what you wanted.

## Code in this folder
- `main.cpp` — runs through each category with a value chosen to expose the loss.

## Gotchas
- `int i = 3.9;` stores `3`. `int i = -3.9;` stores `-3` (truncation toward zero, not floor).
- `float f = 16777217;` — `f` cannot exactly represent that integer. Print it and you'll get `16777216`.
- `unsigned u = -1;` is `4294967295` on a 32-bit `unsigned`. Defined, but a very common bug.

## Run
    make 10.03
