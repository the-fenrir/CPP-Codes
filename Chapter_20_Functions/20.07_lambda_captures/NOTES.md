# 20.7 — Lambda captures

> learncpp.com: https://www.learncpp.com/cpp-tutorial/lambda-captures/

## Why it matters
Captures are how a lambda *remembers* state from the enclosing scope. Without them lambdas are just inline functions. With them you can write small stateful machines — a counter, a running total, a "compare against this threshold" predicate — without declaring a whole class. But every capture is a decision about *value vs. reference* and *lifetime*, and getting it wrong is the #1 lambda bug.

## Key points
- Capture clause syntax inside `[]`:
  - `[x]` — capture `x` by value (a *copy* baked into the closure at construction).
  - `[&x]` — capture `x` by reference (the closure refers to the original).
  - `[=]` — capture all named used variables by value (avoid; implicit captures hide intent).
  - `[&]` — capture all named used variables by reference (same warning).
  - `[x, &y]` — mix.
  - `[this]` / `[*this]` — capture the enclosing object's pointer / a copy of it (member-function lambdas).
- **By-value captures are `const` by default.** Add `mutable` after the parameter list to modify them inside the body — that modifies the *copy*, not the original.
- **By-reference captures see the latest value** and can write back. Lifetime trap: if the lambda outlives the captured variable, you have a dangling reference. Classic case: a lambda capturing a local by reference returned/stored beyond the enclosing function.
- C++14 **init captures**: `[name = expr]` creates a new closure member from an arbitrary expression — needed to move-capture (`[p = std::move(uptr)]`) or to rename / transform.
- A lambda with captures is *not* convertible to a plain function pointer. Use `std::function`, a template parameter, or `auto`.

## Code in this folder
- `main.cpp` — by-value vs. by-reference, `mutable` counter, init-capture for move-only types, and the dangling-reference trap shown safely.

## Gotchas
- `[=]` *looks* like "capture everything" but it captures only what's *used by name* inside the body. Adding a reference to another local later silently makes a new copy.
- `mutable` does **not** turn a value capture into a reference. The change is local to the lambda's copy and is lost when the closure dies (unless the closure persists across calls — then it's a per-closure mutable cell).
- Capturing `this` in a member function copies the *pointer*, not the object. If `*this` dies before the lambda runs, UB. Prefer `[*this]` (C++17+) or capture only the data members you actually need.

## Run
    make 20.07
