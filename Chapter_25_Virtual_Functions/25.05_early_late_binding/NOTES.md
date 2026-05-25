# 25.5 — Early binding and late binding

> learncpp.com: https://www.learncpp.com/cpp-tutorial/early-binding-and-late-binding/

## Why it matters
"Binding" = matching a call site to an implementation. The whole virtual-functions mechanism is a tradeoff between resolving that at compile time (fast, but the static type wins) vs. at run time (slower, but you get polymorphism). Knowing which kind a given call is is the difference between "this code is fine" and "why is the wrong function running?"

## Key points
- **Early (static) binding**: the call target is fixed at compile time from the static type. All non-virtual calls, all calls to free functions, and any call where the compiler can prove the dynamic type, are early-bound.
- **Late (dynamic) binding**: target is selected at run time from the actual dynamic type. Triggered by a virtual call made through a pointer/reference to a base. Implemented via the vtable (25.06).
- Direct calls on an object whose static type matches its dynamic type (`Cat c; c.speak();`) are early-bound even if `speak()` is virtual — the compiler knows. So "virtual" doesn't imply "always dispatched dynamically."
- Late binding costs: one indirection per call (load vtable pointer, index, call). Negligible in I/O-heavy or non-tight-loop code; measurable in tight numeric kernels.
- Function pointers are a manual form of late binding: a single call site can invoke different functions across runs.

## Code in this folder
- `main.cpp` — Shows three calls to the same `virtual` function: (1) direct on a derived (early), (2) through a `Base*` to a derived (late), (3) via a function pointer (late by a different mechanism). Plus a function-pointer demo of early-binding-via-dispatch-table for contrast.

## Gotchas
- Virtual call inside a constructor/destructor is **early-bound to the current class** — the object isn't fully alive / already partly dead. Don't rely on virtual dispatch there.
- Compilers can devirtualize: if the compiler proves the dynamic type, even a virtual call through a pointer can be early-bound. `final` helps it do so.
- "Late binding is slow" is mostly folklore. Profile before pessimizing.

## Run
    make 25.05
