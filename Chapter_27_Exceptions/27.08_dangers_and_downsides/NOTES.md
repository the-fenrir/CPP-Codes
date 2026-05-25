# 27.8 — Exception dangers and downsides

> learncpp.com: https://www.learncpp.com/cpp-tutorial/exception-dangers-and-downsides/

## Why it matters
Exceptions are the right tool for some failures and the wrong tool for others. Before reaching for them, know the costs: cleanup is *your* responsibility (RAII or leaks), there are a few places you must never throw from (destructors, across some boundaries), and the runtime path is genuinely more expensive than a branch. Most "exceptions are slow" complaints are about misuse; the legitimate concerns are around **safety contracts**.

## Key points
- **Cleanup is on you.** Unwinding only destroys automatic objects. Raw `new`-allocated memory, `fopen`'d files, locked mutexes — anything not wrapped in an RAII type — leaks on throw. Solution: never own resources via raw handles in exception-using code.
- **Don't throw out of destructors.** If a destructor throws while another exception is already unwinding, `std::terminate` is called immediately. Destructors should be `noexcept` (and are, by default, in C++11+).
- **Don't throw across module/ABI boundaries.** Exception type info and unwinding tables aren't portable across compilers / shared libraries / language boundaries. The boundary function should catch internally and return a status.
- **Cost model.** The "happy path" (no throw) is roughly free on modern ABIs. The "throw" path is *expensive* — table lookups, destructor calls all the way up. Don't use exceptions for routine control flow.
- **Exception safety guarantees** (Abrahams): *basic* (no leaks, valid but unspecified state), *strong* (operation either succeeds or has no effect — transactional), *no-throw* (cannot fail). Aim for at least basic; promise strong only when you really provide it.

## Code in this folder
- `main.cpp` — three vignettes: (a) RAII vs raw `new` showing the leak, (b) a destructor that *would* throw but doesn't (we log instead), (c) a function offering the strong guarantee via copy-and-swap.

## Gotchas
- "I'll just `delete` in `catch`" — works until someone adds another throw point between the `new` and the `catch`. RAII is not optional; it's how you avoid this.
- A `noexcept` function that throws calls `std::terminate` *immediately* (no unwinding past it). That's a feature for `noexcept` moves (27.9), and a footgun if you mark something `noexcept` and then it throws.
- "Strong guarantee" is hard. Copy-and-swap is the standard recipe: do the work on a copy, swap the result in only if everything succeeded.

## Run
    make 27.08
