# 25.1 — Pointers and references to the base class of derived objects

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pointers-and-references-to-the-base-class-of-derived-objects/

## Why it matters
A `Base*` (or `Base&`) can point/refer to a `Derived` object — that's the whole reason inheritance is useful for runtime polymorphism. But out of the box C++ resolves calls *statically*: through a `Base&`, a `Derived` looks like a `Base`, and `Base::foo()` is what runs even if `Derived` defined its own `foo()`. This lesson plants that fact; 25.02 is how to fix it.

## Key points
- A reference/pointer to `Base` can bind to a `Derived` object — the conversion is implicit and always safe (Derived is-a Base).
- Member access through `Base*`/`Base&` sees only the `Base` portion. Non-virtual function calls are statically dispatched: `b.getName()` calls `Base::getName()` even when the dynamic type is `Derived`.
- This is sometimes what you want — e.g. a function `print(const Base&)` that should accept any derivative — and sometimes a footgun. The fix is `virtual` (next lesson).
- The Derived sub-object *is still there*; only the view is narrowed. A later `dynamic_cast<Derived*>` (25.10) can recover it.

## Code in this folder
- `main.cpp` — Animal/Cat/Dog. A `Cat` is passed by `Animal&` and `Animal*`; the non-virtual `speak()` resolves to `Animal::speak()`. Compare with the direct `Cat` call.

## Gotchas
- Pass-by-value to a `Base` parameter is *not* the same thing — it slices the object (see 25.09). Polymorphism only works through pointer or reference.
- "Base sees Base's members" applies to data members too: a `Base&` bound to a `Derived` can't reach `Derived`-only fields.
- Forgetting `virtual` here is the most common reason `getName()` "doesn't work" — the compiler is doing exactly what you wrote.

## Run
    make 25.01
