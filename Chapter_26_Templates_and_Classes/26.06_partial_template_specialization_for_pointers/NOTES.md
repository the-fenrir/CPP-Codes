# 26.6 — Partial template specialization for pointers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/partial-template-specialization-for-pointers/

## Why it matters
The naïve `Storage<T>` stores a *copy* of `T`. Pass it a `T*` and it dutifully stores a copy of the pointer — which is almost certainly not what the caller wanted. The fix isn't another constructor; it's a **partial specialization for pointer types** that quietly does the right thing (`*m_value` instead of `m_value`). This is one of the most common real-world uses of partial specialization.

## Key points
- Syntax mirrors 26.5: leave `T` free, pin the *shape* as `T*`:
  ```cpp
  template <typename T>
  class Storage<T*> { … };
  ```
- Inside the specialization, `T` is the pointee type (the `*` is in the matching pattern, not in `T`).
- The specialization changes **semantics**: primary = value semantics (owns a copy), `Storage<T*>` = reference / view semantics (does not own the pointee). That asymmetry is a footgun — flag it loudly or eliminate it.
- Three honest options for the ownership mismatch:
  1. **Document it as a view** — caller keeps the pointee alive.
  2. **Forbid raw pointers** in the primary: `static_assert(!std::is_pointer_v<T>);`.
  3. **Deep-copy** in the specialization (e.g. wrap a `std::unique_ptr<T>` made via `new T{*value}`).

## Code in this folder
- `main.cpp` — `Storage<T>` primary plus `Storage<T*>` partial specialization. The primary stores by value; the specialization stores the raw pointer and dereferences on `get()`. A second pointer specialization (`StorageOwning<T*>`) shows the deep-copy variant.

## Gotchas
- Same-shape mismatch: `Storage<int*>` (matches the specialization) and `Storage<int>` (matches the primary) are unrelated types with different semantics. Don't expose one through the other's interface.
- The view variant dangles the moment the caller's object goes out of scope. If you can't guarantee lifetime, choose option 2 or 3.
- A naïve "deep copy" specialization that owns memory needs the rule of three/five — keep it minimal in pedagogical code, but in production reach for `std::unique_ptr`.

## Run
    make 26.06
