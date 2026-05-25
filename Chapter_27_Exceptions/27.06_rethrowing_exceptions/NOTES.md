# 27.6 — Rethrowing exceptions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/rethrowing-exceptions/

## Why it matters
Sometimes a function catches an exception, does *something* with it (log it, add context, release a resource it owned), and then wants to let it keep propagating. That's **rethrowing**. The catch: there are two ways to write it, and one of them silently changes the exception's runtime type. Always use the bare form: **`throw;`**.

## Key points
- **`throw;`** (no operand, only valid inside a `catch`): rethrows the *current* exception object, with its full dynamic type preserved.
- **`throw e;`** (where `e` is the caught variable): throws a *new* exception, sliced to the declared catch type. Avoid.
- Bare `throw;` with no exception in flight calls `std::terminate`. Only use it inside a `catch`.
- Useful for *adding context*: catch a low-level error, log/wrap it, rethrow. The outer handler still sees the original type.
- Modern alternative: `std::throw_with_nested` + `std::nested_exception` lets you wrap-and-throw without losing the original. Beyond this lesson, but worth knowing the name.

## Code in this folder
- `main.cpp` — three rethrow patterns: bare `throw;` (correct), `throw e;` (slicing demo), and a "log-and-rethrow" function that adds context.

## Gotchas
- `throw e;` where `e` is caught by base reference *throws a copy of the base*. The derived parts — and the derived `what()` — are gone. Subtle and very hard to debug.
- Don't catch just to rethrow with no other work. That's pointless; the cost of the catch + unwind isn't free.
- Rethrowing outside any `catch` calls `std::terminate` — `throw;` is not a "throw nothing" no-op.

## Run
    make 27.06
