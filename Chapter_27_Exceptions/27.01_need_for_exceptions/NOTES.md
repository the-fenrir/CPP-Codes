# 27.1 — The need for exceptions

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-need-for-exceptions/

## Why it matters
Return codes are fine when (a) the caller is right next to the failure and (b) the function has a "free" return slot to spare. Neither holds in practice. Constructors have no return value. Operators (`operator[]`, `operator/`) have a fixed signature you can't add an error channel to. Deep call chains turn into `if (err) return err;` boilerplate at every level — and any one missed check silently drops the error. Exceptions solve this by **separating the failure path from the return path**: failure travels out-of-band, all the way to a handler that actually knows what to do.

## Key points
- Return codes pollute the signature: `int divide(int, int, int* out)` instead of `int divide(int, int)`.
- They pollute every call site with mechanical error-propagation code that the human is responsible for not forgetting.
- They can't be used from constructors, operators, or anything whose signature is fixed.
- Sentinel values (`-1`, `nullptr`, `NaN`) collide with valid results and are easy to forget to check.
- Exceptions decouple **where the error is detected** (deep in the stack) from **where it's handled** (wherever you choose to put the `catch`).

## Code in this folder
- `main.cpp` — same divide-by-zero failure handled three ways: sentinel return value, out-param + bool, and exception. Side-by-side so the difference in caller code is obvious.

## Gotchas
- Exceptions are not a license to skip error handling — they just move it. If you don't `catch`, your program terminates.
- Don't use exceptions for *control flow* (loop exits, "not found" lookups). They're for **exceptional** conditions: things the function genuinely cannot deliver on.

## Run
    make 27.01
