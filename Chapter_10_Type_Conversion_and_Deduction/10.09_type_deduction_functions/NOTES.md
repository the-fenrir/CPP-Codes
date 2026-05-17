# 10.9 — Type deduction for functions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/type-deduction-for-functions/

## Why it matters
`auto` works for function *return types* too: write `auto f() { return ...; }` and the compiler infers the return type from the `return` statement. It's mostly a convenience — and a sharp edge if you abuse it. The same C++14 facility powers trailing return types (`auto f() -> int`), which become indispensable once templates and `decltype` enter the picture.

## Key points
- `auto returnType()` deduces the return type from the function's `return` statements.
- All `return` statements must deduce to the **same** type — `return 1;` and `return 1.0;` in the same function is ill-formed (no implicit unification).
- Definition must be visible before any call — the deduction can't happen across a translation unit boundary. Practically: the function must be in a header or before its first use. **Don't use `auto` return on functions in public headers** unless you also expose the body — callers can't infer types from a forward declaration alone.
- **Trailing return type**: `auto f(int x) -> int { return x; }` — equivalent to `int f(int x)`. Why bother? Because the return type can depend on the parameters: `auto add(T a, U b) -> decltype(a + b)`.
- Style: explicit return types remain the default for normal functions. Use `auto`-return when the type is genuinely awkward to spell, or trailing return when it depends on parameters/templates.

## Code in this folder
- `main.cpp` — `auto` return, trailing return, and a tiny template using trailing return to mix types.

## Gotchas
- `auto f() { if (x) return 1; else return 1.5; }` doesn't compile. Both branches deduce different types and the compiler refuses to "pick one."
- `auto`-return makes the API harder to read at the call site — you have to look at the definition to know the return type. Prefer explicit types in interfaces other people consume.
- Don't confuse `auto` *return* (deduce from body) with `auto` *parameter* in a regular function — the latter is only legal in lambdas and abbreviated templates (C++20).

## Run
    make 10.09
