# 15.1 — The hidden `this` pointer and member-function chaining

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-hidden-this-pointer-and-member-function-chaining/

## Why it matters
When you call `obj.foo()`, the compiler quietly passes `&obj` as a hidden first argument named `this`. That's how a member function knows which object's data to touch. Once you see it, two things become possible: **member-function chaining** (return `*this` to enable `a.set(1).set(2).set(3)`) and a precise mental model for the rest of the chapter.

## Key points
- Inside a member function, `this` is a `Foo*` (or `const Foo*` in a `const` member function) pointing to the current object.
- `this->m_x` and `m_x` are the same thing inside a member function — `this->` is optional, useful for disambiguation.
- **Return `*this` from a setter** (return type `Foo&`) and the call becomes chainable: `obj.setA(1).setB(2).setC(3);`.
- For a `const` member function returning `*this`, the return type must be `const Foo&`.
- `this` is an **rvalue pointer**: you can't assign to it (`this = ...`).

## Code in this folder
- `main.cpp` — `StringBuilder`-style class with chainable setters; shows `this` used to disambiguate a parameter from a member.

## Gotchas
- "Returning a reference to a temporary" — if a chain like `Builder{}.set(1).build()` returns a member ref, the temporary's lifetime ends at the `;`. Set up for 15.10 (ref qualifiers).
- `delete this;` is legal but trap-laden; avoid unless you really know what you're doing.

## Run
    make 15.01
