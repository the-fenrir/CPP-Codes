# 14.2 — Introduction to classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-classes/

## Why it matters
You already know `struct`. A `class` is the same machinery with one defaulted difference: members are **private by default**. That single flip is the gateway to encapsulation — by changing the default, the language pushes you to think about *what's safe to expose* before reaching out. Every class concept in the next 15 lessons hangs off this one.

## Key points
- `class Name { … };` — note the trailing semicolon.
- `class` defaults to **private** access; `struct` defaults to **public**. That is the *only* language-level difference.
- Convention: use `struct` for data-bag aggregates (no invariants), `class` when there's *any* rule about how the data should behave.
- A class is a **type**, not an object. `Foo f;` creates the object.
- Member variables are sometimes called **data members** or **fields**.

## Code in this folder
- `main.cpp` — define a simple `Date` class, instantiate, access via member function.
- `struct_vs_class.cpp` — same shape as a struct and as a class; shows what the default access flip costs.

## Gotchas
- Forgetting the `;` after the closing `}` of a class — the compiler error is usually awful and points at the next line.
- "Class" vs. "object" sloppiness — even pros mix these up. Class = blueprint, object = instance.
- A `struct` with member functions is still a struct; the language doesn't care. The convention is what matters.

## Run
    make 14.02
