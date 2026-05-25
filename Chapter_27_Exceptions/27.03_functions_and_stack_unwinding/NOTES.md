# 27.3 — Exceptions, functions, and stack unwinding

> learncpp.com: https://www.learncpp.com/cpp-tutorial/exceptions-functions-and-stack-unwinding/

## Why it matters
The reason exceptions are useful — and the reason RAII works — is **stack unwinding**. When a `throw` finds no handler in the current function, control leaves that function as if it had returned, *and the same thing happens in the caller, and the caller's caller*, until a matching `catch` is found. As each function exits, its local objects are destroyed properly (destructors run). So a `std::lock_guard` releases the lock, a `std::unique_ptr` deletes its pointee, a `std::fstream` closes the file — even though no `return` was ever executed.

## Key points
- A `throw` propagates upward through *every* function on the stack until a handler matches.
- For each function that's exited, **all local objects are destroyed** in reverse construction order — full destructor calls, not just a stack-pointer reset.
- This is why RAII (resources owned by stack objects) is exception-safe by default: leaving the scope = releasing the resource, whether via `return` or `throw`.
- If unwinding reaches `main` with no handler, `std::terminate` is called (next lesson). Destructors of objects *above* the throw site still ran; objects in `main` itself may or may not, depending on the implementation.
- You can re-enter the same scope after the `catch`: code after the `try/catch` runs normally if a handler matched.

## Code in this folder
- `main.cpp` — three nested functions; the innermost throws, the outermost catches. Each function has a local `Trace` object whose destructor logs, proving unwinding ran cleanup at every level.

## Gotchas
- Unwinding only destroys **automatic** (stack) objects. Raw-`new`'d memory leaks. Hence: don't use raw `new` in exception-using code; use smart pointers / containers.
- A destructor that itself throws **during unwinding** calls `std::terminate`. Destructors must not throw. (More in 27.8.)
- Whether `main`'s locals are destroyed when an exception escapes `main` is implementation-defined. Don't rely on it — catch in `main` if you care.

## Run
    make 27.03
