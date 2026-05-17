# 7.10 — Sharing global constants across multiple files

> learncpp.com: https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/

## Why it matters
"I want `constexpr double pi = 3.14159...` visible in every `.cpp` in the project, without each TU getting its own copy." Modern C++ has exactly one right answer to this: **put `inline constexpr` constants in a header.** Anything else (defining `const` in a header, `extern const`, macros) has at least one drawback that the inline-constexpr form fixes.

## Key points
- **The recipe**: put `inline constexpr T name{ value };` inside a `namespace Constants { ... }` in a single header. Every `.cpp` that includes the header sees the same value.
- `inline` ⇒ all TUs share one definition; one address, one copy, no ODR violation, no `extern` declaration needed.
- `constexpr` ⇒ usable at compile time (array sizes, `static_assert`, template args).
- `namespace Constants` ⇒ qualifier prevents collisions and tells the reader "these are constants."
- For C++14 fallback (no inline variables): use `constexpr` in a header (each TU gets its own copy — fine for true scalars, wasteful for complex types) OR `extern const` with a single defining TU (loses constexpr-ness).

## Code in this folder
This is a **multi-file** lesson.

- `constants.h` — `inline constexpr` constants in `namespace Constants`.
- `physics.cpp` — uses the constants in one TU.
- `main.cpp` — uses them in another TU, prints the same values.

You won't *see* the "one address" property at runtime (it's a link-time guarantee), but the program builds and runs without ODR violations precisely because of `inline`.

## Gotchas
- Plain `constexpr T name{ ... };` in a header (no `inline`) compiled under C++14 gives each TU its own copy. Same value, but different addresses, and if the type is heavy (e.g. `std::string_view` to a stored literal) it's wasteful.
- `const T name{ ... };` in a header: internal linkage by default (7.6), so again each TU gets a copy. Works for scalars; awkward when the constant is large.
- Don't use `#define` for constants in C++ — no type, no namespace, no scope, no debugger visibility.

## Run
    make 7.10
