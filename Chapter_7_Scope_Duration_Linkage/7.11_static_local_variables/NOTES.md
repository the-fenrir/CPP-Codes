# 7.11 — Static local variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/static-local-variables/

## Why it matters
A `static` local variable has **local scope** but **static duration**. It's visible only inside its function — but it survives between calls. This gives you "state that belongs to one function" without polluting the global namespace. It's the C++ answer to "I want a function-private counter" and the basis of the Meyers Singleton pattern.

## Key points
- `static` inside a function = static duration, local scope, no linkage.
- Initialized **once**, on first entry to its declaration. The initializer runs at most once per program run, and is **thread-safe** since C++11 ("magic statics").
- Retains its value across calls. Default-initialized to zero (unlike non-static locals).
- Common uses: a per-function counter, lazy initialization of an expensive object, the Meyers Singleton (`static T& instance() { static T x; return x; }`).
- `static` here means something completely different from `static` at file scope (7.6) — same keyword, three meanings depending on context (file scope, class scope, function scope).

## Code in this folder
- `main.cpp` — a `next_id()` function with a `static int` counter, plus a "first-call?" pattern.

## Gotchas
- Initial value is set **on first entry** to the declaration line, not at program start. If the function is never called, the variable is never initialized.
- Returning a pointer/reference to a static local is fine (the storage outlives the call) but creates hidden coupling — the same caveats as a global, just with narrower scope.
- Static locals make the function impure and harder to test in isolation. Use deliberately, not by reflex.

## Run
    make 7.11
