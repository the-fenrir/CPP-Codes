# 19.1 — Dynamic memory allocation with `new` and `delete`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/dynamic-memory-allocation-with-new-and-delete/

## Why it matters
Static and automatic storage need a size known at compile time and live in a small (~1 MB) stack. Dynamic allocation asks the OS for memory at runtime from the much larger heap — the only way to size an object based on user input, build data structures that outlive their creating function, or hold more than a megabyte of state. The cost: *you* are now responsible for giving it back.

## Key points
- `new T` returns a `T*` to one freshly constructed `T` on the heap. `new T{x}` initializes it.
- `delete p` runs `T`'s destructor and returns the memory. **Exactly one** `delete` per `new`.
- `delete nullptr` is a no-op — safe by design, so you don't need null checks.
- After `delete p`, `p` is a **dangling pointer**. Set `p = nullptr;` unless `p` is about to leave scope anyway.
- `new` throws `std::bad_alloc` on failure. `new (std::nothrow) T` returns `nullptr` instead — check before use.
- Three failure modes you must recognize on sight:
  1. **Memory leak** — reassign or lose `p` before `delete`.
  2. **Double delete** — call `delete p` twice.
  3. **Use-after-free** — dereference `p` after `delete p`.

## Code in this folder
- `main.cpp` — allocates one `int`, uses it, deletes it. Shows `std::nothrow`. Comments mark every leak/dangle that would appear if you mistyped.

## Gotchas
- Pairing rules: `new` ↔ `delete`. `new[]` ↔ `delete[]` (next lesson). Crossing them is undefined behavior.
- Two pointers to the same object: after one of them `delete`s, the *other* is dangling. Ownership must be unambiguous.
- Prefer `std::unique_ptr<T>` (or `std::make_unique<T>(...)`) over raw `new`/`delete`. It's a one-line drop-in that makes leaks structurally impossible. Raw `new` exists in this chapter for teaching; in real code, reach for the smart pointer.

## Run
    make 19.01
