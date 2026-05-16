# 14.9 — Introduction to constructors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-constructors/

## Why it matters
Once your data members are private, the *outside world* can't initialize them directly — but they still need values. **Constructors** are the special member functions that run automatically when an object is created. They're how a class guarantees "no instance of me exists in an unsafe state." If 14.5–14.8 said "hide your data," 14.9 says "and make sure it starts out valid."

## Key points
- Same name as the class, no return type — not even `void`.
- Called automatically on object creation. You don't call it yourself.
- Can have parameters and be overloaded like normal functions.
- Constructor parameters use **initializer-list syntax**: `Foo f{ 1, 2 };` or `Foo f(1, 2);` (the `{}` form is preferred — narrowing-safe).
- Without any user-declared constructor, the compiler generates a default one that does no member initialization (members keep whatever default they had).
- Constructors *can* assign in their body, but **member initializer lists** (14.10) are strictly better. Body assignment is shown here only because the next lesson exists to replace it.

## Code in this folder
- `main.cpp` — multiple constructors, including a `Date` with parameters; shows what happens when you skip initialization.

## Gotchas
- `Foo f();` does **not** create an object. It declares a function taking no args and returning `Foo`. Use `Foo f{};` for default-construction.
- A constructor body runs *after* all members are already constructed. By then it's too late to *initialize* — you can only *assign*. (This is the setup for 14.10.)

## Run
    make 14.09
