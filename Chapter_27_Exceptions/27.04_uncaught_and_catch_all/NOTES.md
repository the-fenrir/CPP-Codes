# 27.4 — Uncaught exceptions and catch-all handlers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/uncaught-exceptions-catch-all-handlers/

## Why it matters
An exception that escapes `main` doesn't crash with a stack trace — it calls **`std::terminate`**, which calls `std::abort` by default. That's almost never what you want as the *last visible behavior* of your program. The fix is a top-level safety net: catch-all (`catch (...)`) at the boundary, log what happened, decide whether to recover or abort cleanly. Inside the body of the program, `catch (...)` is usually a code smell — it tells you nothing about what failed — but at the *outermost* level it's the correct shape.

## Key points
- If no handler matches, `std::terminate()` is called → `std::abort()` → program ends. Destructors of locals above the throw ran during unwinding; destructors in `main` may not.
- **`catch (...)`** is the "catch every type of exception" handler. It must be the *last* catch on a `try`.
- Inside `catch (...)` you cannot inspect the exception object directly — you have no name for it. You can rethrow with bare `throw;` to forward it.
- The idiomatic top-level shape: one `try` wrapping `main`'s body, one or two specific `catch`es, then a `catch (...)` as a last resort. This is the only place `catch (...)` belongs by default.
- Inside business logic, prefer specific `catch (const SomeError&)` — you generally need to know what failed to do anything useful.

## Code in this folder
- `main.cpp` — wraps a function that may throw any of several types, demonstrating a layered `catch (const std::exception&)` + `catch (...)` boundary.

## Gotchas
- `catch (...)` swallows everything — including bugs you'd rather see crash (`std::bad_alloc`, contract violations). Use it at the top of `main`, not deep in business code.
- The default `std::terminate` is hostile to debugging on some platforms (no message, no core file by default). Catch in `main` and `std::cerr << e.what()` yourself.
- Inside `catch (...)` you can rethrow with `throw;` — that preserves the original exception type. `throw e;` would not work because there is no `e`.

## Run
    make 27.04
