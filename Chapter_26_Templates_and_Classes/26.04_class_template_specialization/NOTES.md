# 26.4 — Class template specialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/class-template-specialization/

## Why it matters
Sometimes a whole class needs a different implementation for one specific type. The canonical example is `std::vector<bool>` — instead of storing one `bool` per byte, it packs eight booleans into a single byte. Same interface, different guts. Class template specialization is the language feature that makes that possible.

## Key points
- Syntax: `template<> class Storage8<bool> { … };` after the primary template is declared.
- The specialization is a **completely independent class**. Different members, different layout, different invariants — you only have to keep the public interface compatible *by convention* (the compiler doesn't enforce it).
- You can also specialize **individual member functions** when only one piece needs to differ:
  ```cpp
  template<> void Storage<double>::print() { … }
  ```
- Put specializations in the **same header** as the primary template. If a TU sees only the primary, it'll instantiate the wrong version — and you won't get a compile error, just wrong behavior.

## Code in this folder
- `main.cpp` — `Storage8<T>` storing 8 of `T` in an array, plus a `Storage8<bool>` specialization that packs the bits into a single `std::uint8_t`. `sizeof` proves it.

## Gotchas
- A specialization seen *after* the type is already instantiated is an error. Order matters: declare specializations before any use.
- "Same interface as primary" is a discipline thing, not a compiler thing. Drift between primary and specialization is a common source of confusing bugs.
- Class template specialization is the *right* tool for member-level behavior changes — partial specialization is needed when only some of the parameters are pinned (see 26.5).

## Run
    make 26.04
