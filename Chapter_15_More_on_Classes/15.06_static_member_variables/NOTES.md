# 15.6 — Static member variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/static-member-variables/

## Why it matters
A `static` member is **per-class**, not per-object: every instance shares one copy. That's how you model "the next ID to hand out," "an instance counter," or "a class-wide config value" without resorting to free globals. Globals leak into other code's namespace; static members are scoped, access-controlled, and travel with the class.

## Key points
- Declare inside the class: `static int s_count;`. Convention: `s_` prefix.
- Pre-C++17, a *definition* (allocating storage) was required in exactly one `.cpp`: `int Foo::s_count = 0;`.
- C++17 **`inline static`** members can be initialized in the class body — no separate definition needed: `inline static int s_count{ 0 };`.
- `static const` integer members can be initialized in-class (always have been).
- `static constexpr` works in-class for any literal type.
- Static members are still subject to access specifiers (`private static` is normal).

## Code in this folder
- `main.cpp` — `Widget` counting how many instances exist using an `inline static` (C++17) counter.

## Gotchas
- A `static` member is shared across all instances *and* across all translation units. If you initialize it twice (legacy + inline), you'll get a linker error or worse.
- Static **local** variables in a member function are also one-per-program — sometimes useful, sometimes a footgun.

## Run
    make 15.06
