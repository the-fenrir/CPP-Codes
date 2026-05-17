# 10.4 — Narrowing conversions, list initialization, and constexpr initializers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/narrowing-conversions-list-initialization-and-constexpr-initializers/

## Why it matters
Most numeric conversions just warn. **List (brace) initialization** is the one place the language draws a hard line: if the conversion *might* lose information, it's a compile error. That's why `int x{ 3.9 };` won't compile but `int x = 3.9;` will. This is the single best reason to default to brace initialization.

## Key points
- A **narrowing conversion** is a numeric conversion that may lose value or precision: FP → integer, wider FP → narrower FP, wider integer → narrower integer, signed ↔ unsigned (in cases where representation differs).
- Inside `{ ... }` initialization, narrowing is **ill-formed** — a compile error, not just a warning.
- Exception: a **constexpr** source value the compiler can prove is exactly representable in the destination type is *not* a narrowing conversion. So `short s{ 100 };` compiles (`100` fits, source is constexpr), but `short s{ runtimeInt };` does not.
- Caveat for FP→integer: many compilers (clang in particular) treat *any* `double → int` brace init as narrowing, even with an exact constexpr like `5.0`. The standard says it's value-preserving, the implementations are stricter. Write `static_cast<int>(5.0)` if you really need it.
- This is *the* practical reason to brace-init: it makes the compiler your friend on accidental loss.

## Code in this folder
- `main.cpp` — shows valid brace inits, and includes the bad cases in commented-out form so the file still builds.

## Gotchas
- The exception is narrow: the source must be `constexpr` AND exactly representable. `double d = 5.0; int x{ d };` is rejected — `d` is not constexpr. And clang refuses `int x{ 5.0 };` too — FP→int is treated as narrowing regardless.
- `short s{ someInt };` is narrowing even when `someInt` happens to be small — the compiler reasons about types, not runtime values, unless the source is constexpr.
- `float f{ 5.0 };` is narrowing (`5.0` is a `double` literal). Write `5.0f` or use `double f{ 5.0 };`.

## Run
    make 10.04
