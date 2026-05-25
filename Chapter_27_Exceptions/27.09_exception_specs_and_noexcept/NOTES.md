# 27.9 — Exception specifications and `noexcept`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/exception-specifications-and-noexcept/

## Why it matters
`noexcept` is a **contract**, not an optimization knob you sprinkle for performance. Marking a function `noexcept` says: "this function will not let an exception escape; if it does, terminate the program." That contract matters because the standard library *queries* it (`noexcept(...)` expression) and uses the answer to pick faster code paths — most importantly, deciding whether `std::vector` will move or copy your elements when it grows (27.10). The C++98 `throw(...)` specifications are deprecated and removed; only `noexcept` matters now.

## Key points
- `void f() noexcept;` — promises `f` won't escape via exception. If one does, `std::terminate` is called immediately.
- `noexcept(expr)` — conditional. `void g() noexcept(some_constexpr_bool);` lets templates propagate the property.
- **`noexcept` is an operator** too: `noexcept(expr)` is a `constexpr bool` saying "is this expression non-throwing?". Used to *query* a function's contract without calling it.
- Default rules: **destructors, deallocation functions, and (usually) implicitly-declared special members are `noexcept`**. Most other functions are not, by default.
- Mark these `noexcept` when you can: move constructors, move assignment, swap, destructors (already), simple accessors. Don't mark something `noexcept` if it can legitimately fail.
- Removed in C++17: dynamic exception specifications (`throw(SomeType)`). The keyword `throw()` as a synonym for `noexcept` is also deprecated.

## Code in this folder
- `main.cpp` — declares one throwing and one `noexcept` function, queries them with the `noexcept` operator, and shows that calling a `noexcept` function that *does* throw terminates the program (demo wrapped behind a flag so the harness doesn't abort).

## Gotchas
- Marking a function `noexcept` and then having it throw doesn't unwind — it `terminate`s. So `noexcept` is a *strong* promise.
- Templates: `noexcept` on a template function only holds when the operations it performs are themselves `noexcept`. Use `noexcept(noexcept(expr))` to propagate.
- Backward compat: old `throw()` specifications are not equivalent — they had different behavior (a violation called `unexpected`, not `terminate`). Don't use them.

## Run
    make 27.09
