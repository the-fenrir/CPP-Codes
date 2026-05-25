# 25.10 — Dynamic casting

> learncpp.com: https://www.learncpp.com/cpp-tutorial/dynamic-casting/

## Why it matters
Once you have a `Base*`, you've thrown away the static type information for the derived parts. Usually that's fine — virtual dispatch is enough. Sometimes you genuinely need the derived back ("this is a `Cat*`, call `purr()` on it"). `dynamic_cast` does the type-checked downcast: succeeds and returns the derived pointer if the dynamic type really is that derived; returns `nullptr` otherwise. Safe but slow.

## Key points
- `dynamic_cast<Derived*>(basePtr)` — returns `nullptr` if the dynamic type isn't `Derived` (or a class derived from it). Test before dereferencing.
- `dynamic_cast<Derived&>(baseRef)` — throws `std::bad_cast` on failure (no null reference to return). Use the pointer form unless you're sure the cast must succeed.
- Requires that the involved types are **polymorphic** — i.e. have at least one virtual function. (RTTI lives next to the vtable.)
- Runtime cost is non-trivial: it walks the class hierarchy. Don't put it in tight inner loops; prefer virtual functions for behavior, `dynamic_cast` for occasional escape hatches (visitor, double-dispatch, plugin systems).
- "Upcasting" (Derived* → Base*) is implicit and free — you don't need `dynamic_cast` for that.

## Code in this folder
- `main.cpp` — A small `Animal` hierarchy with `Cat` and `Dog`. A function takes `Animal*`, uses `dynamic_cast<Cat*>` to opportunistically call a `Cat`-only `purr()`. Also shows the reference form throwing on failure.

## Gotchas
- If you find yourself sprinkling `dynamic_cast` throughout the codebase to switch on types, that's a smell: you've reinvented a virtual function in a less safe form. Add a virtual to the base instead.
- `static_cast<Derived*>(basePtr)` compiles too — but skips the runtime check. If the dynamic type is wrong, you get UB. Only use `static_cast` when you have other proof of the type (e.g. CRTP, tag-dispatched code path).
- `typeid(*p) == typeid(Derived)` is a different (stricter) check — exact type, no derived-of-derived. Sometimes that's actually what you want; usually `dynamic_cast` is.

## Run
    make 25.10
