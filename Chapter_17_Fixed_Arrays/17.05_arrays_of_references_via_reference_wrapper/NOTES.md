# 17.5 — Arrays of references via `std::reference_wrapper`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/arrays-of-references-via-stdreference_wrapper/

## Why it matters
You can't put references in a container. `int& arr[3]` isn't legal C++, and `std::array<int&, 3>` doesn't compile either — references aren't *objects*, they don't have a size or address you can put in an array slot. When you genuinely need "an array of references to existing things" (e.g. an observation collection, not an owning store), `std::reference_wrapper<T>` from `<functional>` is the workaround.

## Key points
- `std::reference_wrapper<T>` is a tiny class that holds a pointer but advertises itself as a reference: assignable, copyable, rebindable.
- Use it as the element type: `std::array<std::reference_wrapper<int>, 3> refs { a, b, c };`.
- `refs[0].get()` returns the underlying `int&`. Implicit conversion to `T&` works in most contexts: `refs[0] = 99;` rebinds-ish in some libraries, but for `std::reference_wrapper` direct assignment forwards to the wrapped object — *use `.get()` if you want clarity*.
- `std::ref(x)` and `std::cref(x)` are factory helpers that produce a `reference_wrapper` for `x`. Most natural when populating: `std::array refs { std::ref(a), std::ref(b), std::ref(c) };`.
- The original objects must outlive the wrappers — `reference_wrapper` is non-owning and silently dangles if the referent dies.

## Code in this folder
- `main.cpp` — three `int`s, an array of `reference_wrapper<int>` aliasing them, mutate through the wrapper, observe the originals change.

## Gotchas
- `std::reference_wrapper<int> r = 42;` doesn't compile — you can't make a reference to a temporary literal.
- Passing a `reference_wrapper` to a function expecting `int&` requires the implicit conversion to fire; sometimes it doesn't (e.g. through templates). Call `.get()` if you hit a deduction failure.
- Use this for *observation*. For ownership, use `std::array<T, N>` directly or pointers.

## Run
    make 17.05
