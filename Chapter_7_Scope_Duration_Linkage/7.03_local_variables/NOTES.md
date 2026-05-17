# 7.3 — Local variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/local-variables/

## Why it matters
Local variables are the C++ default — they have **block scope**, **automatic duration**, and **no linkage**. Understanding these three properties for the simplest case makes the rest of chapter 7 land cleanly: globals differ in *all three* of those properties; static locals differ in *one*.

## Key points
- **Scope** = block scope: visible from declaration to end of enclosing `{}`.
- **Duration** = automatic: storage created on entry to the block, destroyed at the closing `}`. Stack-allocated.
- **Linkage** = none: another translation unit can declare `int x` with no relation to this one.
- Function parameters are local variables of the function body block.
- Locals are *not* zero-initialized by default. `int x;` leaves garbage; `int x{};` value-initializes to `0`. Always prefer the latter.
- A local can be `const`/`constexpr`; that affects mutability, not duration or scope.

## Code in this folder
- `main.cpp` — locals in nested blocks, lifetime printed via a small RAII trace type.

## Gotchas
- Returning a pointer/reference to a local is a dangling reference — its storage is gone the moment the function returns. Compilers warn on the obvious case; non-obvious cases will silently corrupt at runtime.
- "Local" is about *scope*, not "on the stack." A local can hold a `std::vector` whose elements live on the heap; the vector *object* itself is still automatic.

## Run
    make 7.03
