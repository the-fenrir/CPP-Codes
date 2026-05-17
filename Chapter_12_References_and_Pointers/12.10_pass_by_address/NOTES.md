# 12.10 — Pass by address

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pass-by-address/

## Why it matters
Pass-by-address means the function receives a *pointer*. Conceptually similar to pass-by-reference — the function can read/write the caller's object — but with explicit syntax (`*p`, `&x`) and explicit nullability. In modern C++ this is the right choice in narrow situations: when "no object" is a legitimate argument, or when interoperating with C APIs.

## Key points
- Signature: `void f(T* p)`. Caller passes `&x` or `nullptr`. Inside, `*p` reads/writes the pointee.
- The function **must** consider null. Forgetting the null check is a major source of bugs.
- Pass-by-address vs pass-by-reference: same capability (read/write the caller's object), different defaults around nullability and syntax.
- For non-null required inputs that may be modified, prefer **`T&`**. For optional inputs (may be absent), prefer **`std::optional`** (12.15), then `T*`.
- Pass-by-address makes mutation visible at the call site (`f(&x)` vs `f(x)`), which some style guides like — but most modern guidance is fine with `T&` and good function naming.

## Code in this folder
- `main.cpp` — `incrementOrIgnore(int*)` showing the null check pattern.

## Gotchas
- The call site `f(&x)` vs `f(x)` only documents *that* something is being passed by address, not *what* the function does with it. Naming still matters.
- Don't take `&x` of a temporary or expression: `f(&(a + 1))` is a compile error.
- For "in" parameters that are large, `const T&` is still better than `const T*` — same semantics, no null check, no `(*p).member`.

## Run
    make 12.10
