# 14.15 — Class initialization and copy elision

> learncpp.com: https://www.learncpp.com/cpp-tutorial/class-initialization-and-copy-elision/

## Why it matters
You'll write `Foo f = makeFoo();` and expect a copy (or move). Surprisingly often, the compiler *skips* the copy entirely — that's **copy elision**. Knowing what's elided and what isn't is the difference between guessing your code's performance and reading it. Since C++17, certain elisions are **mandatory** — so you can rely on them.

## Key points
- **Copy elision** = constructing the object directly into its destination, skipping the copy/move that would otherwise happen.
- **Mandatory** (C++17): returning a *prvalue* (`return Foo{...};`), constructing from a prvalue (`Foo f = Foo{...};`).
- **Optional (NRVO)**: returning a *named* local variable that matches the return type. Most compilers do it; not guaranteed by the standard.
- Even when copy elision happens, the copy/move constructor **must still exist and be accessible** (e.g. not `= delete`d).
- Forms of initialization to know: copy init `Foo f = x;`, direct init `Foo f(x);`, brace init `Foo f{x};`, value init `Foo f{};`, default init `Foo f;`.

## Code in this folder
- `main.cpp` — copy ctor that prints when called, then we observe how many times it actually runs across construction patterns.

## Gotchas
- "I expected 3 copies and got 0" — copy elision. Read the assembly or add tracing to confirm.
- Returning `std::move(localVar)` *prevents* NRVO. Don't do it.
- Brace init `Foo{x}` is preferred over `Foo(x)` because it rejects narrowing conversions (`Foo{ 3.14 }` won't quietly truncate to `int`).

## Run
    make 14.15
