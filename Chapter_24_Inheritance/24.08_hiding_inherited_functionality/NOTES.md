# 24.8 — Hiding inherited functionality

> learncpp.com: https://www.learncpp.com/cpp-tutorial/hiding-inherited-functionality/

## Why it matters
Sometimes the derived class is a *narrower* version of the base — it inherits the implementation but shouldn't expose every base member. C++ lets you change a base member's access in the derived class, or delete it outright. This is "hiding" rather than "overriding."

## Key points
- **Change access of a single inherited member**: inside the derived class, write `using Base::member;` under the access level you want (commonly to demote a `public` base function to `private`/`protected` in the derived).
- This only works for members the derived class can already *see* — you can widen `protected` to `public`, or narrow `public` to `private`/`protected`. You can't access `private` base members.
- **Delete an inherited function for derived users**: redeclare it in the derived class and mark `= delete;`. Calling it on a `Derived` is now a compile error.
- Hiding by name lookup: any function in the derived class with the same name hides *all* overloads of that name from the base, even ones with different signatures. Pull them back with `using Base::name;`.

## Code in this folder
- `main.cpp` — `Base` exposes `do_a()` and `do_b()`. `Derived` makes `do_a()` private to its callers, and `delete`s `do_b()` for derived consumers.

## Gotchas
- Hiding via `using` changes access **as seen from outside**; member functions of `Derived` can still call the original. That's what you usually want.
- `=delete` only blocks calls *through the derived type*. Code that has a `Base&` can still call the function — you haven't actually removed it from the base subobject.
- An overload set in the base is hidden as a *set* the moment the derived defines anything with that name. Easy to lose overloads silently.

## Run
    make 24.08
