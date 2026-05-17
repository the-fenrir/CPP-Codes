# 9.4 — Detecting and handling errors

> learncpp.com: https://www.learncpp.com/cpp-tutorial/detecting-and-handling-errors/

## Why it matters
Most function bodies have one happy path and several sad paths. The shape of the function — what it returns on bad input, what it logs, whether it asks the caller to recover or bails out — is a *design decision*, not a syntax decision. This lesson gives you the vocabulary (precondition, invariant, postcondition, recoverable vs. non-recoverable) and the menu of responses.

## Key points
**The vocabulary:**
- **Precondition** — must be true *before* the function runs. e.g. `denominator != 0` for `divide(a, b)`.
- **Invariant** — must remain true *during* execution. e.g. inside a class: "balance ≥ 0".
- **Postcondition** — must be true *after* the function returns. e.g. "result is sorted".

**The menu of responses when something goes wrong inside a function:**
1. **Handle it locally** — silently clamp, default, or skip. Use when the caller doesn't need to know.
2. **Return an error value** — `-1`, `0`, `false`, `std::nullopt`, `std::optional<T>`. Caller must check.
3. **Return + out-parameter for an error code** — older C-ish style.
4. **Throw an exception** (chapter later) — bubbles up automatically.
5. **Abort the program** — `std::abort`, `std::exit`, `assert` failure. Reserve for *non-recoverable* states.

**Recoverable vs. non-recoverable:**
- **Recoverable** — caller can retry, fall back, or ask the user again. Bad user input is recoverable.
- **Non-recoverable** — invariant violated; continuing would corrupt data. Abort.

**`std::cerr` vs `std::cout`:**
- `std::cout` for normal output. `std::cerr` for diagnostics — unbuffered, often goes to a different stream when redirected.

## Code in this folder
- `main.cpp` — a `safeDivide` shown in three flavors: silent default, `std::optional<int>`, and abort-on-precondition-violation. Each demonstrates one row of the menu above and prints what the caller experiences.

## Gotchas
- **"Return -1 on error" only works if -1 isn't a valid result.** For unconstrained ranges, prefer `std::optional<T>`.
- **Don't `abort()` on bad input.** Bad input is recoverable; bugs are not. Confusing the two turns a bad password prompt into a crash.
- **Logging is not handling.** Writing to `std::cerr` and returning a wrong answer is *worse* than returning an error — it gives the caller no signal *and* corrupts results.
- **The caller chooses recovery, not the callee.** Library functions that pop modal dialogs or call `exit()` are unusable in any non-trivial program.

## Run
    make 9.04
