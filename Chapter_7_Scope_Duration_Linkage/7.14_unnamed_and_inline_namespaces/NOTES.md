# 7.14 — Unnamed and inline namespaces

> learncpp.com: https://www.learncpp.com/cpp-tutorial/unnamed-and-inline-namespaces/

## Why it matters
Two specialized namespace forms tie up loose ends from 7.6 and 7.9.

- **Unnamed namespace** = modern, idiomatic replacement for file-scope `static`. Everything inside gets internal linkage automatically.
- **Inline namespace** = a versioning tool: the inner names are reachable as if they were in the outer namespace. Used heavily by the standard library (`std::__1::`, ABI-versioning).

## Key points

### Unnamed namespaces
- `namespace { ... }` — no name. Everything declared inside has internal linkage, restricted to the current TU.
- Effectively equivalent to applying `static` to every entity inside, but works for *types* too (file-scope `static` can't make a type TU-local).
- Modern C++ recommendation: prefer unnamed namespaces over file-scope `static` for new code.

### Inline namespaces
- `inline namespace V1 { ... }` — names inside `V1` are reachable both as `V1::name` and as just `name` from the enclosing namespace.
- Lets a library expose `Lib::foo` while internally it's `Lib::V1::foo`. Bumping to `V2` (also inline-namespaced) swaps the default without breaking explicit `Lib::V1::foo` callers.
- Outside library/ABI use cases, you usually don't need this.

## Code in this folder
- `main.cpp` — an unnamed namespace with a helper used only in this TU, and an `inline namespace V2` demonstrating both qualified and unqualified access.

## Gotchas
- Putting an unnamed namespace **in a header** defeats the point — every including TU gets its own private copy, almost certainly not what you want.
- Inline namespaces are transparent to **name lookup**, not to **type identity**: `Lib::V1::T` and `Lib::V2::T` are distinct types even if both are inline.

## Run
    make 7.14
