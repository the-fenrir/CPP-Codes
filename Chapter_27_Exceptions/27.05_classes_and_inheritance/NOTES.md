# 27.5 — Exceptions, classes, and inheritance

> learncpp.com: https://www.learncpp.com/cpp-tutorial/exceptions-classes-and-inheritance/

## Why it matters
Throwing an `int` or a `std::string` works but tells you almost nothing. Throw a **class** instead: it can carry context (file name, line number, parameters that caused the failure), and — most importantly — it can participate in an inheritance hierarchy. That hierarchy lets a single `catch (const BaseError&)` handle a whole family of related failures, and lets callers choose how specific they want to be.

## Key points
- Define exception types as classes, ideally deriving from `std::exception` (or one of its standard children like `std::runtime_error` / `std::logic_error`).
- Override `what()` to return a useful message (`virtual const char* what() const noexcept`).
- **Catch by `const Base&`**: avoids slicing, polymorphic dispatch works, you see the derived type's `what()`.
- Order `catch` blocks from **most-derived to least-derived**. The first match wins, so a `catch (const std::exception&)` above a `catch (const MyError&)` makes the second one unreachable.
- The standard hierarchy is your default vocabulary: `std::logic_error` (programmer bugs: `invalid_argument`, `out_of_range`) vs. `std::runtime_error` (environmental failures: `range_error`, `system_error`).

## Code in this folder
- `main.cpp` — a tiny `ArrayError → IndexError, EmptyError` hierarchy. A single `catch (const ArrayError&)` handles both, and you still see the specific message via virtual `what()`.

## Gotchas
- **Catching by value slices.** `catch (ArrayError e)` will lose the `IndexError` part and call `ArrayError::what()`. Always catch by `const&`.
- Don't inherit from `std::exception` *just to add a constructor*; inherit from `std::runtime_error` / `std::logic_error` which already take a `std::string` message in their constructor.
- Avoid throwing raw `int`/`const char*`/`std::string`. Standard libs and other people's code don't catch those — your exception escapes to `catch (...)` or `std::terminate`.

## Run
    make 27.05
