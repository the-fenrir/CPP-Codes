# 12.11 — Pass by address (part 2)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/pass-by-address-part-2/

## Why it matters
Part 1 introduced the mechanic. Part 2 covers the design choices: when to use it, how to model optional output, why "set this pointer to point at something" needs a *reference-to-pointer* or a *pointer-to-pointer*, and the rule of thumb that "pass-by-address is for nullable inputs."

## Key points
- **Optional input** is the canonical legitimate use of `T*`. If null is meaningful ("logger if you have one, otherwise skip"), pass-by-address fits.
- **Optional output**: pass `T*` so the caller can opt out by passing `nullptr`. The callee checks before writing.
- **Pass-by-address to change *which* object the caller's pointer refers to** needs `T*&` (reference to pointer) or `T**` (pointer to pointer). Easy to get wrong.
- A pointer parameter that's "always required, never null" should be a reference. The signature should reflect the contract.
- `nullptr` defaults: `void f(T* p = nullptr)` lets the caller omit the argument — handy for optional parameters.

## Code in this folder
- `main.cpp` — three patterns: optional logger; optional output param; reassigning the caller's pointer.

## Gotchas
- "Pass a pointer so it's faster than copying" is the wrong reason — that's what `const T&` is for. Use pointers when you genuinely need null or rebinding.
- Reassigning the *parameter pointer* (`p = &other;`) does **not** affect the caller's pointer — same lvalue-vs-rebind confusion as references. You need `T*&` or `T**` to do that.
- A function returning a pointer raises ownership questions: who deletes it? Default to non-owning, or use `std::unique_ptr`/`std::shared_ptr` (later chapter).

## Run
    make 12.11
