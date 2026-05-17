# 7.2 — User-defined namespaces and the scope resolution operator

> learncpp.com: https://www.learncpp.com/cpp-tutorial/user-defined-namespaces-and-the-scope-resolution-operator/

## Why it matters
Once a program spans multiple files written by multiple people, **name collisions** are inevitable. Namespaces partition the global namespace into named regions so two libraries can both have a `print()` without fighting. `std::` is the same mechanism — nothing magical about it.

## Key points
- `namespace Foo { ... }` declares a named scope. Refer to its members as `Foo::name`.
- The **scope resolution operator** `::` selects which scope to look in. `::name` (with no prefix) means the *global* namespace explicitly.
- Namespaces can be **reopened** in the same or another file — that's how `std::` ends up with thousands of names across many headers.
- Nested namespaces: `namespace A::B { ... }` (C++17) is shorthand for `namespace A { namespace B { ... } }`.
- Namespace **aliases**: `namespace fs = std::filesystem;` — local to the scope they appear in.

## Code in this folder
- `main.cpp` — two `print()` functions in two namespaces, qualified calls, a nested namespace, and an alias.

## Gotchas
- A function defined inside `namespace Foo` is `Foo::funcName` — it does *not* live in the global namespace.
- Reopening a namespace doesn't reset it; you're adding to the existing set of names.
- `using namespace Foo;` brings everything in — fine in a `.cpp`, dangerous at file scope, terrible in a header. See 7.13.

## Run
    make 7.02
