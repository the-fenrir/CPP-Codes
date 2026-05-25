# 27.2 — Basic exception handling

> learncpp.com: https://www.learncpp.com/cpp-tutorial/basic-exception-handling/

## Why it matters
Three keywords do the whole job: **`throw`** raises an exception, **`try`** marks a region of code that might raise one, and **`catch`** handles it. The shape `try { … } catch (T e) { … }` is the only syntax you really need on day one. Everything else in this chapter is refinements to *what* you throw, *how* you catch it, and *what happens in between*.

## Key points
- `throw expr;` constructs a temporary "exception object" from `expr` and starts looking for a handler.
- A `try` block has one or more `catch` blocks attached. The first matching `catch` (by type) wins.
- Match is by **type**, not by value. `catch (int)` catches any thrown `int`.
- If no handler matches, execution leaves the function — and keeps leaving — until one does. Unwinding (next lesson).
- A handler's body runs *instead of* the rest of the `try`. Control then resumes after the last `catch`.
- You can throw any copy-constructible type, but you should throw class objects (27.5) so you can catch by base reference.

## Code in this folder
- `main.cpp` — minimal `throw`/`try`/`catch` skeleton plus one example showing why catch-order matters.

## Gotchas
- `catch (T e)` makes a *copy* of the exception object. For class types, **catch by `const T&`** — same reason you pass class arguments by const-ref.
- Catching by value can slice a derived exception down to its base type, losing the actual error info.
- A `try` with no `catch` is a syntax error. So is a `catch` not attached to a `try`.

## Run
    make 27.02
