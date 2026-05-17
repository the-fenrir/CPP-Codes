# 7.8 — Why (non-const) global variables are evil

> learncpp.com: https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/

## Why it matters
Non-const globals look convenient ("I'll just put it up here so everyone can see it") and turn into the worst kind of bug surface. The harm isn't immediate; it's that the cost grows with the size of the program while the convenience stays constant. This lesson is the *justification* for everything 7.6/7.7 set up.

## Key points
- **Action at a distance.** Any function can read or write the global; you can't audit "who touches `g_state`" by looking at a call site.
- **Hidden coupling.** Two functions that both touch a global are coupled even though their signatures don't say so. Reorder calls and behavior changes.
- **Untestable.** A function that reads `g_state` can't be unit-tested in isolation; you must set up the global first, and tests interfere with each other unless you reset it.
- **Initialization order across TUs is undefined.** Global `A` constructed using global `B` in a different `.cpp` is a coin flip.
- **`const`/`constexpr` globals are fine.** They have no mutable state, no action-at-a-distance, no init-order hazard (constexpr is computed at compile time).
- Default reflex: pass the data in as a parameter, or wrap it in a class. If something genuinely is program-global (e.g. a logger), at least confine its mutation to one well-named module.

## Code in this folder
- `main.cpp` — two functions that *both* touch the same non-const global. The same call sequence produces different results depending on order — the point of "hidden coupling."

## Gotchas
- "But I'll only mutate it from one place" — true today; in six months someone else won't see that rule.
- Thread-safety: every non-const global is a data race waiting to happen the moment you add a second thread.
- A `static` global (internal linkage) is *still* a non-const global within that TU; the file-scope confinement only narrows the blast radius.

## Run
    make 7.08
