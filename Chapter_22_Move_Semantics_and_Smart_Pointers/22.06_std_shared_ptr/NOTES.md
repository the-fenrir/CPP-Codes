# 22.6 — `std::shared_ptr`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdshared_ptr/

## Why it matters
`std::shared_ptr<T>` allows multiple owners for the same object via a reference count. The last owner to leave scope deletes the object. Use it only when ownership truly is shared — otherwise `unique_ptr` is cheaper and clearer.

## Key points
- Construct with `std::make_shared<T>(args...)`. It allocates the object and the control block (refcount, weak count, deleter) **in one allocation** — faster than `shared_ptr<T>{ new T }` and exception-safe.
- Copying a `shared_ptr` increments the refcount; destruction decrements. Reaching zero ⇒ object deleted; reaching zero weak+strong ⇒ control block deleted.
- Two `shared_ptr`s built from the **same raw pointer** (rather than copying one from the other) have **independent control blocks** ⇒ double-delete. The classic foot-bullet (see chapter quiz Q3).
- Convertible to `weak_ptr` (22.7) for non-owning observation.
- `shared_ptr<T>` is roughly 2× the size of a raw pointer (data ptr + control-block ptr) and modifies the refcount atomically — not free.
- Prefer `unique_ptr` until you actually need sharing.

## Code in this folder
- `main.cpp` — basic sharing with `use_count()` reported at each step, plus the **wrong way** (two `shared_ptr`s from the same raw pointer) commented out with the explanation.

## Gotchas
- `make_shared` keeps the object's storage alive until the last `weak_ptr` is destroyed — because object + control block share one allocation. If you have huge `T` and many `weak_ptr`s, prefer `shared_ptr<T>{ new T }`. Rare.
- Cycles leak (lesson 22.7). `weak_ptr` is the fix.
- `enable_shared_from_this<T>` is the right way for a member function to get a `shared_ptr` to itself. Never construct a fresh `shared_ptr` from `this`.

## Run
    make 22.06
