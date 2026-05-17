# 12.14 — Type deduction with pointers, references, and const

> learncpp.com: https://www.learncpp.com/cpp-tutorial/type-deduction-with-pointers-references-and-const/

## Why it matters
`auto` is convenient — but its deduction rules **drop references and top-level `const` by default**. `auto x = ref;` makes a copy, not an alias. Misunderstanding this silently introduces unintended copies (slow) or unintended decoupling (the `auto` "alias" doesn't actually alias).

## Key points
- `auto` strips top-level `const` and references. `auto x = constRef;` deduces `T` (no const, no ref).
- To preserve them, ask for them explicitly:
  - `auto&` — bind a reference.
  - `const auto&` — bind a const reference. Common in range-based for: `for (const auto& e : v)`.
  - `auto*` — deduce a pointer; equivalent to `auto` for pointer init, but reads more clearly.
- `auto` **does** preserve low-level (pointee) `const`. `auto p = constIntPtr;` deduces `const int*`.
- For pointers, `const` on the pointee is part of the pointee type, not top-level on the pointer — so it survives.
- Rule of thumb in `for` loops:
  - reading only → `const auto&`
  - mutating → `auto&`
  - value semantics needed (you're going to modify a copy) → `auto`

## Code in this folder
- `main.cpp` — same source, four `auto` forms, prints the deduced behavior.

## Gotchas
- `auto x = vec[0];` copies the element. `auto& x = vec[0];` aliases it. `for (auto e : v)` copies every element on every iteration.
- `const auto` and `auto const` mean the same thing.
- `auto&&` is the *forwarding reference* (universal reference) — special rules in templates; in non-template code it binds to anything but isn't usually what you want.
- `decltype(auto)` preserves references and constness exactly as the initializer — useful for return-type deduction when you want pass-through semantics.

## Run
    make 12.14
