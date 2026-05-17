# 8.14 — Generating random numbers using Mersenne Twister

> learncpp.com: https://www.learncpp.com/cpp-tutorial/generating-random-numbers-using-mersenne-twister/

## Why it matters
`std::mt19937` is the Mersenne Twister engine that ships with the standard library — the practical default PRNG for everyday use (games, simulations, generating test inputs). Its period (2^19937 − 1) is absurdly long, its statistical quality is good for non-cryptographic purposes, and it's portable. Knowing exactly how to wire it up with `<random>` is the everyday skill for this lesson; everything else builds on the engine + distribution split.

## Key points
- `std::mt19937` produces 32-bit unsigned ints. `std::mt19937_64` produces 64-bit. Both have the same API.
- **Seed once.** Constructing an engine is moderately expensive; seeding it on every call costs both time and randomness quality. The standard idiom is:
  ```cpp
  static std::mt19937 mt{ std::random_device{}() };
  ```
  inside the function that uses it — `static` makes it persist across calls.
- A **distribution** maps engine output to a useful range/shape. Pair an engine with the distribution you need; never use modulo on the engine output directly (it biases the result).
  - `std::uniform_int_distribution<int>{ lo, hi }` — both bounds inclusive.
  - `std::uniform_real_distribution<double>{ lo, hi }` — `[lo, hi)`.
  - `std::bernoulli_distribution`, `std::normal_distribution`, ...
- The distribution object is cheap; you can construct it once and reuse it, or construct it on each call. Reusing is slightly faster.
- Don't use `<random>` for crypto. Even mt19937's state can be recovered from ~624 consecutive outputs. For secrets, use a CSPRNG (`/dev/urandom`, BoringSSL, libsodium, etc.).

## Code in this folder
- `main.cpp` — the standard pattern: a free function `rollDie(int sides)` that holds a `static` engine and constructs a distribution per call. Roll several dice, then a few normally-distributed samples to show how easy other distributions are.

## Gotchas
- **`uniform_int_distribution{lo, hi}` is inclusive on both ends** — `[lo, hi]`. `uniform_real_distribution{lo, hi}` is half-open `[lo, hi)`. Easy to mix up.
- A *single* `random_device` call to seed is fine on every desktop platform, but `mt19937` has 19937 bits of state and you're seeding with 32 bits of entropy. For applications that care, seed with a `std::seed_seq` over several `random_device` calls.
- `static` engine inside a free function is fine for single-threaded code. For multi-threaded, you want one engine per thread (e.g. `thread_local`).

## Run
    make 8.14
