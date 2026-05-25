# 27.7 — Function try blocks

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-try-blocks/

## Why it matters
A regular `try` inside a constructor body can't catch exceptions thrown from the **member initializer list** — by the time the body runs, init has already finished (or aborted). A **function try block** wraps the entire function, including the init list, so you can observe a member's constructor throwing. It's the only tool for this specific job, and it has one very tight rule: a function-try-block in a constructor or destructor **must** rethrow (or end up rethrowing); you can never "swallow" the failure and pretend the object exists.

## Key points
- Syntax: replace the function body's `{ … }` with `try { … } catch (…) { … }`. No surrounding braces.
- In a **constructor**, the `try` covers both the member initializer list and the body. This is the only place it has unique power.
- The caught exception **is implicitly rethrown** at the end of the `catch` block if you don't explicitly rethrow or terminate. There is no way to return normally from a constructor function-try-block after a member init throws — the object never finished constructing, so it cannot exist.
- Inside the `catch`, you must not access non-static members — the ones that *did* construct have been destroyed already, and ones that didn't never existed.
- For non-constructor functions, a function try block is equivalent to a `try` wrapping the whole body — there's no real reason to prefer it.

## Code in this folder
- `main.cpp` — a class whose member throws on construction; a function-try-block catches it, logs, and lets the implicit rethrow do its job. `main` catches the resulting exception.

## Gotchas
- "I can recover from a constructor failure by absorbing the exception in a function-try-block." **No.** The object is dead. The exception leaves regardless.
- Don't reach for function-try-blocks in destructors. Destructors should not throw (27.8); if a member's destructor does, you generally call `std::terminate`, you don't handle it.
- For *any* normal function, prefer the plain `try { … } catch { … }` inside the body — easier to read, identical behavior.

## Run
    make 27.07
