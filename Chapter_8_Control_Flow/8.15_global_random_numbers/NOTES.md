# 8.15 — Global random numbers (Random.h)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/

## Why it matters
8.14 showed *one* engine inside *one* function. Real programs need random numbers from many places. Re-seeding a fresh engine on every call is wasteful and reduces randomness quality (each fresh engine starts at the beginning of its sequence). The fix is to share **one** engine across the whole program. learncpp.com's lesson introduces a `Random.h` header that does exactly this. In this repo we inline the same idea so each lesson stays standalone — no shared header to copy around. Same effect, less coupling.

## Key points
- A program-wide engine should live somewhere with **program lifetime**: an `inline` variable in a namespace (`inline` variables are C++17 and may live in a header without ODR issues), or a `static` local inside an accessor function (Meyers singleton).
- Construct it **once**, seeded once, from `std::random_device` (or a `seed_seq` for more entropy).
- Provide free helper functions that take a min/max and return a uniform int — the call site shouldn't have to assemble an engine + distribution by hand.
- A typical helper interface:
  ```cpp
  int get(int min, int max);                  // uniform int [min, max]
  double get(double min, double max);         // uniform real [min, max)
  ```
- Thread safety: a single global engine isn't thread-safe. For multi-threaded use, make it `thread_local` (each thread gets its own engine, seeded independently). For single-threaded programs, a plain `inline` global is fine.

## Code in this folder
- `main.cpp` — defines a tiny `Random` namespace at the top of the file with an `inline` engine and `get(min, max)` helpers; then uses them from a few "client" call sites. This is the same shape as the site's `Random.h`, just folded into one file so the lesson builds standalone.

## Gotchas
- An `inline` engine in a real header gets one instance across the whole program (good). A plain `namespace { std::mt19937 mt; }` (anonymous namespace, no `inline`) in a header gets one instance **per translation unit**, each seeded independently — usually not what you want.
- Don't reseed the global engine. The point is a single long sequence.
- Avoid `std::rand()` and `std::srand()`. They share a single global state too, but the API is much worse and the underlying generator's quality is implementation-defined.

## Run
    make 8.15
