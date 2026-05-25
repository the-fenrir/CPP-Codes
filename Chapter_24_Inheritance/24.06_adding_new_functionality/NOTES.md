# 24.6 — Adding new functionality to a derived class

> learncpp.com: https://www.learncpp.com/cpp-tutorial/adding-new-functionality-to-a-derived-class/

## Why it matters
Often the base is fine and you just need the derived to *do more*. Adding members on the derived side is the cleanest way to extend behavior without touching code that other derived classes also rely on.

## Key points
- A derived class can add brand-new data members and member functions on top of what it inherits.
- Those new members are only visible through a `Derived` object (or pointer/reference to derived) — not through a `Base*` pointing at a `Derived`.
- This is the right move when only *some* derivatives need the new capability. Pushing it into the base forces every other derived class to carry it too.
- Adding to a derived class never modifies the base — base-only callers continue to compile and behave as before.

## Code in this folder
- `main.cpp` — base `Animal` with `speak()`; derived `Dog` *adds* `fetch()`. A `Dog` can do both; an `Animal&` can only do `speak()`.

## Gotchas
- A `Base*` or `Base&` can't see derived-only members. Accessing them requires the derived static type, or a `static_cast<Derived*>(...)` once you've confirmed the dynamic type — usually a smell.
- Don't push capability into the base just to avoid a cast. If only `Dog` has a `fetch`, only `Dog` should declare one.

## Run
    make 24.06
