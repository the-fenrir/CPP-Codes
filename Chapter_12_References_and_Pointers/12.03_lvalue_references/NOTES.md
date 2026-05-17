# 12.3 — Lvalue references

> learncpp.com: https://www.learncpp.com/cpp-tutorial/lvalue-references/

## Why it matters
An **lvalue reference** is just another name for an existing object. No copy, no indirection syntax, no nullability. It's the single most-used compound type in idiomatic C++ — function parameters, range-based-for loop variables, structured bindings all lean on it.

## Key points
- Declaration: `T& name { object };` — the `&` is part of the *type*, not an operator here.
- A reference **must** be initialized at the point of declaration. There is no "default-constructed" reference.
- A reference is **not rebindable**: `ref = other;` does **not** make `ref` point to `other`; it assigns `other`'s value into whatever `ref` already refers to.
- Once bound, `ref` and the original object are interchangeable in every expression.
- A reference cannot bind to an rvalue (use `const T&` for that — next lesson).
- References don't have their own storage in the abstract machine; in practice compilers often implement them as pointers, but that's an implementation detail.

## Code in this folder
- `main.cpp` — bind, read, write, and the "ref = other doesn't rebind" trap.

## Gotchas
- `int& r;` — error. Must initialize.
- `int& r = 5;` — error. Can't bind a non-const lvalue ref to a literal/rvalue.
- `int& r = x; r = y;` — does **not** rebind `r` to `y`; it copies `y`'s value into `x`. This is the #1 surprise.
- A reference to a reference doesn't exist as a type — `int& &` collapses (reference collapsing) and isn't directly written. Templates use this; you don't.

## Run
    make 12.03
