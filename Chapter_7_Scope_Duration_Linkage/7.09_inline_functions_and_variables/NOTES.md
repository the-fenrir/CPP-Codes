# 7.9 — Inline functions and variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/

## Why it matters
The `inline` keyword has been **redefined** in modern C++. It no longer means "compiler please inline this function for speed" — that decision is the optimizer's, with or without the keyword. In modern C++ `inline` means: **this entity may be defined in multiple translation units, and the linker must treat all those definitions as the same one.** That's what makes header-only definitions safe.

## Key points
- `inline` on a function/variable = "exempt from the ODR's one-definition-per-program rule, *provided* every definition is token-for-token identical." All TUs share one entity at link time.
- Functions defined **inside** a class body are implicitly `inline`. So are `constexpr` functions.
- `inline` enables **inline variables** (C++17): a single `inline constexpr` variable declared in a header is shared across every TU that includes it. This is the underpinning of 7.10.
- `inline` has nothing to do with optimizer inlining anymore. The compiler decides inlining based on its own cost model; the keyword is purely a linkage/ODR signal.
- Use cases:
  - Small free functions you want to keep in the header (next to a class declaration, say).
  - `inline constexpr` global constants in a shared header (7.10).
  - Header-only libraries.

## Code in this folder
- `main.cpp` — an `inline` free function and an `inline constexpr` variable in a single TU. The cross-TU benefit needs multiple files; see 7.10 for the real-world example.

## Gotchas
- `inline` does NOT mean "internal linkage." An inline variable in a header is shared across TUs (external linkage with a vague linkage rule), not duplicated like `static` would be. That's the whole point.
- All definitions of an inline entity must be **identical**. Different versions in different TUs = undefined behavior, often silent.
- `inline` on a non-static class member function is redundant if the function is defined in the class body (already implicitly inline) but legal.

## Run
    make 7.09
