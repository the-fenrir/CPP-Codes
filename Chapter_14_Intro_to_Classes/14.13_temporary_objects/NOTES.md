# 14.13 — Temporary class objects

> learncpp.com: https://www.learncpp.com/cpp-tutorial/temporary-class-objects/

## Why it matters
Anytime you write `Foo{ 1, 2 }.doSomething()` or `bar(Foo{ 1, 2 })`, you're using a **temporary** — an unnamed object that exists only for the duration of the surrounding expression. Temporaries are everywhere in idiomatic C++; understanding them is the first step toward understanding copy elision (14.15) and move semantics later.

## Key points
- A temporary is created when you construct an object without naming it: `Foo{ 1, 2 }`.
- It lives until the end of the **full expression** (typically the semicolon), then is destroyed.
- Temporaries are **rvalues** — they can bind to `const T&` and to `T&&`, but not to plain `T&`.
- A `const T&` parameter bound to a temporary extends the temporary's lifetime to match the reference's lifetime.
- Common use: passing constructed-on-the-fly arguments without naming a local.

## Code in this folder
- `main.cpp` — temporaries as function arguments, as method receivers, and the const-ref lifetime extension.

## Gotchas
- A non-const reference (`T&`) **cannot** bind to a temporary. `void f(Foo&)` rejects `f(Foo{1,2})`.
- Don't keep a pointer or non-extending reference to a temporary past the semicolon. UB.
- A temporary is destroyed at the *end of the full expression*, not at the closing brace of its statement — that distinction trips people in chained calls.

## Run
    make 14.13
