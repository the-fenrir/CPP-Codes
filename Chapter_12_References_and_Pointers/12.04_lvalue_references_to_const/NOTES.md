# 12.4 — Lvalue references to const

> learncpp.com: https://www.learncpp.com/cpp-tutorial/lvalue-references-to-const/

## Why it matters
A `const T&` is the workhorse parameter type in C++. It can bind to *anything that can be read* — lvalues, rvalues, temporaries, literals, derived-class objects — without copying and without granting modification rights. Almost every function that takes a non-trivially-copyable input uses `const T&`.

## Key points
- `const T& ref { obj };` — binds to `obj` and promises not to modify it through `ref`. `obj` itself may still be modifiable by other names.
- A `const T&` may bind to a **non-const** object (you just can't modify it through this alias).
- A `const T&` may bind to an **rvalue** or **temporary** — and **extends its lifetime** to match the reference's scope. This is the special rule that makes `const T&` parameters work for literals.
- You may have multiple references with different `const`-ness to the same object simultaneously.
- A non-const reference may **not** bind to a const object — that would silently strip `const`.
- Implicit conversions can happen at binding time: `const double& d { 5 };` binds `d` to a *temporary* `double` materialized from `5`.

## Code in this folder
- `main.cpp` — binding to lvalue, rvalue, temporary; lifetime extension; the conversion gotcha.

## Gotchas
- **Lifetime extension applies only to direct binding**, not to a sub-expression of a returned reference. `const T& r = makeVector().front();` — the *vector* is the rvalue being bound, then `front()` returns a reference into it; but here you're binding `r` to the result of `.front()`, not to the vector — the vector dies, `r` dangles. Bind to the object you want to keep alive, not to a piece of it.
- `const T& r = 5;` works for `T = int`. `const int& r = some_double;` works but creates a *temporary int* — `r` doesn't follow later changes to `some_double`. Easy to write by accident.
- `const` here means "const **through this reference**", not "the referred object is const." A `const int&` to a non-const `int` is fine.

## Run
    make 12.04
