# 24.9 — Multiple inheritance

> learncpp.com: https://www.learncpp.com/cpp-tutorial/multiple-inheritance/

## Why it matters
C++ lets a class inherit from more than one base. It's powerful but routinely abused. Knowing when it actually pays off — and knowing the pitfalls (name collisions, ambiguity, the diamond problem) — keeps you from designing yourself into a corner.

## Key points
- Syntax: `class C : public A, public B { ... };` — list each base with its own inheritance mode.
- Construction order follows the order bases are listed in the derived class declaration. Destruction reverses it.
- A `C` object contains an `A` subobject *and* a `B` subobject. Members of both are accessible from `C`.
- **Ambiguity**: if both bases define a member with the same name, an unqualified reference is a compile error. Disambiguate with `A::name` or `B::name`.
- **Diamond problem**: if `B` and `C` both inherit from `A`, then `D : public B, public C` gets two `A` subobjects. Solve with **virtual inheritance** (`class B : virtual public A`) — out of routine scope, mostly for library authors.
- Strong recommendation: prefer composition or "single concrete base + multiple pure-interface bases" over generic multiple inheritance.

## Code in this folder
- `main.cpp` — `Teacher` and `Researcher` both have a `work()`; `Professor` inherits from both and disambiguates the call.

## Gotchas
- Two bases each with their own copy of a same-named member is ambiguity, not "the derived gets to pick" — the compiler will refuse.
- The diamond problem is the canonical reason `virtual` inheritance exists. Reach for it only when you understand the cost (extra indirection, fragile init order).
- Most "I want multiple inheritance" cases are better as: one real base for state, additional bases that are *abstract interfaces only* (no data).

## Run
    make 24.09
