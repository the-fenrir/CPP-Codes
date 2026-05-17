# 13.9 — Default member initialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/default-member-initialization/

## Why it matters
"Built-in members start uninitialized" is a footgun. Default member initializers fix the value *at the point of declaration*, so an `Employee e{};` is fully initialized whether you remembered to brace-init it or not.

## Key points
- **Default member initializer**: `int id{ 0 };` inside the struct gives `id` a default value used whenever the member isn't provided by an initializer.
- Aggregate init still wins for any member it covers; defaults fill in the rest.
- `Employee e;` (no braces, no defaults) leaves built-ins indeterminate. `Employee e;` *with* defaults uses them. `Employee e{};` value-initializes — equivalent to all-defaults in practice.
- Mixing: declare a default for *every* member that has a sensible neutral value. Members without a clear default should be required to be passed in.
- Use **brace** initializers in the default (`int id{ 0 };`), not `=` (`int id = 0;`), to keep narrowing detection consistent. Both compile; the brace form is the chapter's convention.

## Code in this folder
- `main.cpp` — `Employee` with defaults on every member; shows that `e;`, `e{};`, and `e{ 1 }` all leave the rest sane.

## Gotchas
- Adding a default to a member doesn't change aggregate-status (still an aggregate).
- A default member initializer is only used when the member isn't otherwise initialized by aggregate init.

## Run
    make 13.09
