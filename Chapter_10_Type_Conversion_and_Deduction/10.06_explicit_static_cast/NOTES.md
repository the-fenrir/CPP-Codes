# 10.6 — Explicit type conversion (casting) and `static_cast`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/

## Why it matters
Sometimes the conversion *is* what you mean: print a `char` as its integer value, divide two `int`s as a `double`, suppress a narrowing warning at a single deliberate point. That's an **explicit cast**. C++ provides several flavors; `static_cast` is the safe, named one for everyday numeric/related-type conversions and the only one you should reach for in this chapter.

## Key points
- Syntax: `static_cast<DestType>(expression)`.
- What `static_cast` does:
  - Any well-defined implicit conversion (numeric promotion, numeric conversion, etc.).
  - Conversions between related types when the compiler can prove safety (e.g. enum ↔ underlying integer).
- What `static_cast` does *not* do:
  - Strip `const` (use `const_cast`, and reconsider why you need to).
  - Reinterpret one pointer/reference type as an unrelated one (`reinterpret_cast` — almost never the right answer).
- The other casts to recognize but not reach for:
  - **C-style cast** `(int)x` — too permissive; can silently do dangerous reinterpret/const conversions. Avoid in C++.
  - **Functional cast** `int(x)` — same problems as C-style, despite looking nicer.
  - `dynamic_cast` — runtime downcasts in polymorphic hierarchies (chapter 25).
- A cast is documentation: it says "I know this loses information; do it anyway." Make sure that's actually true at the call site.

## Code in this folder
- `main.cpp` — `static_cast` to fix int-division averages, to print a `char` as a number, and to silence a deliberate narrowing in brace init.

## Gotchas
- `static_cast<int>(3.9)` is `3`, not `4`. Casts truncate; they don't round. Use `std::round` first if you want rounding.
- A cast is not an assertion — it does not check the value at runtime. `static_cast<char>(300)` happily overflows.
- Wrap-the-whole-expression mistake: `static_cast<double>(a / b)` casts the *result* of integer division. You want `static_cast<double>(a) / b`.

## Run
    make 10.06
