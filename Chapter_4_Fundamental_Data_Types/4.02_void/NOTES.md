# 4.2 — Void

> learncpp.com: https://www.learncpp.com/cpp-tutorial/void/

## Why it matters
`void` means "no type." It's the one fundamental type that can't be the type of a *value*. Knowing where `void` legitimately appears keeps you from misusing it (and saves you from one C-ism still in textbooks).

## Key points
- `void` is an **incomplete type** — declared but never defined. The compiler can't allocate storage for it, so `void x;` is illegal.
- Legitimate use #1: **function return type** for functions that return nothing — `void doStuff() { ... }`.
- Legitimate use #2: **`void*`** (covered later, 19.5) — a pointer that has lost its element type. Useful in low-level code; avoid otherwise.
- Empty parameter lists: write `int f()`, not `int f(void)`. The `f(void)` form is a deprecated C-ism kept around for backward compatibility.

## Code in this folder
- `main.cpp` — a `void` function and the preferred empty-parameter syntax.

## Gotchas
- `void f(void)` and `void f()` mean the same thing in C++. In C they differ (`f()` means "unspecified parameters"). Don't carry the C habit.
- You cannot do arithmetic on a `void*` and you cannot dereference it. Cast to a concrete pointer type first.

## Run
    make 4.02
