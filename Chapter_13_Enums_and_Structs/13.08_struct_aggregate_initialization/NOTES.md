# 13.8 — Struct aggregate initialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/struct-aggregate-initialization/

## Why it matters
A struct without a user-defined constructor is an **aggregate** — and aggregates have a special initialization syntax that maps each brace-list element to the member in declaration order. That's how almost all the structs in this chapter get filled in.

## Key points
- **Aggregate**: a class type (struct/class/array) with no user-declared constructors, no private non-static data members, no base classes, no virtual functions. Most plain structs qualify.
- **Aggregate init** uses braces: `Employee e{ 1, "Alice", 50000.0 };`. Elements map to members in **declaration order**.
- **Missing trailing elements get value-initialized**: `Employee e{ 1, "Bea" };` → `salary=0.0`. Built-in types get zero, strings get empty, etc. (Some compilers warn on partial aggregate init with `-Wmissing-field-initializers`; use designated initializers or fill the rest explicitly to silence it.)
- **Empty braces** value-initialize everything: `Employee e{};` → all members zeroed / default-constructed.
- **Designated initializers** (C++20): `Employee e{ .id = 1, .salary = 50000.0 };`. Must follow declaration order; you can skip members but you can't reorder.
- **Narrowing** inside braces is a compile error: `int x{ 3.5 };` is rejected. That's a feature.

## Code in this folder
- `main.cpp` — every form of aggregate init: positional, partial, empty, designated. Shows the narrowing rejection (commented out).

## Gotchas
- `Employee e;` (no braces) leaves built-in members uninitialized. Always use `{}` for safety.
- Reordering members in a struct silently changes the meaning of positional aggregate init at every callsite. Designated initializers protect against this.

## Run
    make 13.08
