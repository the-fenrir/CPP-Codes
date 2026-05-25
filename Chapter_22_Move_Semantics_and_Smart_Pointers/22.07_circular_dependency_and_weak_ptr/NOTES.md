# 22.7 — Circular dependency issues with `std::shared_ptr`, and `std::weak_ptr`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/circular-dependency-issues-with-stdshared_ptr-and-stdweak_ptr/

## Why it matters
Two `shared_ptr`s pointing at each other form a cycle whose refcounts never reach zero, even after every external owner is gone. Result: a leak that smart pointers can't fix. `std::weak_ptr` breaks the cycle: it observes a `shared_ptr`-managed object without contributing to the refcount.

## Key points
- Cycle example: `Person` has `shared_ptr<Person> partner` and two `Person`s point at each other. When `main` returns, each `Person`'s refcount stays at 1 → no destruction → leak.
- **Fix**: make the back-edge a `weak_ptr<Person>`. Forward edge stays `shared_ptr`. Now the chain has an "owner direction" and the cycle is broken.
- `weak_ptr` API:
  - `weak_ptr<T> w = some_shared_ptr;` — does *not* affect refcount.
  - `w.expired()` — has the object been destroyed?
  - `w.lock()` — returns a `shared_ptr<T>`; **empty** if expired, valid (refcount-incremented) if alive. This is the *only* safe way to dereference.
- Other use case: caches and parent→child / child→parent trees. The "back-pointer" is almost always the `weak_ptr` side.

## Code in this folder
- `main.cpp` — two `Person`s that befriend each other. Run once with `shared_ptr<Person>` partners (leak), once with `weak_ptr<Person>` partners (clean). Print dtor messages to see the difference.

## Gotchas
- A `weak_ptr` does not extend lifetime. Once the last `shared_ptr` is gone, `w.lock()` returns empty, even if the control block (and `weak_count`) keeps the *control block* alive.
- Don't try to dereference a `weak_ptr` directly — there's no `*` or `->`. Always go through `lock()` and check for null.
- A class with a `weak_ptr` member is still copyable. Sharing a `weak_ptr` is cheap and well-defined.

## Run
    make 22.07
