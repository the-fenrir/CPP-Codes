# 7.6 — Internal linkage

> learncpp.com: https://www.learncpp.com/cpp-tutorial/internal-linkage/

## Why it matters
**Linkage** answers: "if two translation units declare the same name at file scope, do they refer to the *same* entity?" *Internal* linkage means **no** — each TU gets its own copy, hidden from the linker. This is the right default for helpers you don't want leaking out of a single `.cpp` file. The modern preferred spelling is an **unnamed namespace** (7.14), but understanding `static` at file scope is still required reading.

## Key points
- A *non-const* global at file scope has **external** linkage by default.
- A *const* or *constexpr* global at file scope has **internal** linkage by default.
- The `static` keyword *at file scope* forces internal linkage on whatever it's applied to (including non-const globals and free functions). (`static` inside a class or function means something else entirely.)
- Internal-linkage entities can be defined in a header included from multiple TUs without ODR issues — each TU gets its own copy. This is rarely what you actually want; prefer `inline` (7.9) for true sharing.
- Two `.cpp` files can each define their own `static int s_count;` without colliding — they're separate variables that happen to share a name.

## Code in this folder
This is a **multi-file** lesson. The Makefile detects the header and links all `.cpp` together.

- `internal.h` — declares two functions.
- `a.cpp` — defines a `static int s_count;` and bumps it; exposes one of the functions.
- `b.cpp` — defines its *own* `static int s_count;`. Same name, different variable.
- `main.cpp` — calls both, shows the two counters are independent.

## Gotchas
- `static` at file scope is a deprecated *spelling* for "internal linkage" in modern style (C++ once even discussed deprecating the keyword for that meaning). Use an unnamed namespace (`namespace { ... }`) for new code.
- A `const`/`constexpr` global *is already* internal-linkage — don't add `static` redundantly.
- "Internal linkage" is sometimes called "static storage with internal linkage" — duration and linkage are independent properties; both are static here.

## Run
    make 7.06
