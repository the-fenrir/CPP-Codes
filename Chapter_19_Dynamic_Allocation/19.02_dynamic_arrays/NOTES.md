# 19.2 — Dynamically allocating arrays

> learncpp.com: https://www.learncpp.com/cpp-tutorial/dynamically-allocating-arrays/

## Why it matters
A C-style array's length must be a compile-time constant. `new[]` removes that restriction: you can ask for `n` elements where `n` is a runtime value (user input, file size, parsed config). This is the closest raw analog to `std::vector` — and the lesson exists mostly so you can see why `std::vector` is what you actually want.

## Key points
- `new T[n]` allocates `n` consecutive `T`s. `n` may be a runtime expression. Returns `T*` pointing to the first element.
- `new T[n]{}` value-initializes (zero for arithmetic types). `new T[n]{ a, b, c }` initializes the first elements; the rest are value-initialized.
- **`delete[] p`**, not `delete p`. The runtime tracks the array length so it knows how many destructors to run; `delete` (scalar) won't honor that.
- The array length is *not* recoverable from the pointer. Carry it alongside or, better, stop using raw arrays.
- `std::sort(p, p + n)` works on a `T*` range — the algorithm doesn't care that `p` came from `new[]`.
- Cannot resize a `new[]`-allocated array. You'd have to `new[]` a bigger one, copy, and `delete[]` the old. This is exactly what `std::vector` does for you.

## Code in this folder
- `main.cpp` — reads `n` names from input redirected in (no interactive prompt at test time), allocates `new std::string[n]`, sorts with `std::sort`, prints, and `delete[]`s. A constant test input is hard-coded so the program runs unattended under `make`.

## Gotchas
- `delete p` on a `new T[n]` is undefined behavior — typically a crash or silent leak.
- `new T[0]` is allowed and returns a non-null pointer you must still `delete[]`.
- Length is not stored where you can read it. If you find yourself passing `(ptr, length)` pairs around, you've reinvented half of `std::vector` — finish the job.
- Preferred modern form: `std::vector<T> v(n);` or `std::vector<T> v{ a, b, c };`. Same semantics, frees itself, knows its own size, can grow.

## Run
    make 19.02
