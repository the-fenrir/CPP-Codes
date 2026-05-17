# 12.8 — Null pointers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/null-pointers/

## Why it matters
A pointer can represent "no object" by holding a sentinel value: the null pointer. Unlike a reference, which must always alias a real object, a pointer's nullability is intrinsic — and is also the #1 source of bugs if you forget to check.

## Key points
- The C++11 null pointer literal is `nullptr` (of type `std::nullptr_t`). It implicitly converts to any pointer type.
- Use `nullptr`, **not** `NULL` (a macro, usually `0`) and **not** the literal `0`. `nullptr` is type-safe — it can't accidentally pick the `int` overload.
- `T* p { nullptr };` is the canonical "I have no target yet" initialization.
- Dereferencing a null pointer is **undefined behavior**, not a guaranteed segfault.
- A pointer compares `false` in a boolean context iff null; idiom: `if (p) { ... }` or `if (!p) { ... }`.
- "Dangling" pointer (points at memory no longer valid) ≠ "null" pointer. Setting a freed pointer to `nullptr` after `delete` turns one into the other and makes the bug detectable.

## Code in this folder
- `main.cpp` — `nullptr` init, null check, the safe pattern: check before dereferencing.

## Gotchas
- `NULL` works for legacy interop but breaks overload resolution: `void f(int); void f(int*);` — `f(NULL)` calls the `int` overload, `f(nullptr)` calls the pointer overload.
- `if (p == 0)` and `if (p == nullptr)` both work; prefer the latter for clarity.
- A null check protects against null, **not** against dangling. There's no general way to ask "is this pointer still valid?" — it's your responsibility to track lifetime.

## Run
    make 12.08
