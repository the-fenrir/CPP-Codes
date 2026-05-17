# 8.13 — Introduction to random number generation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/

## Why it matters
Computers are deterministic. "Random" numbers from a program are produced by a **pseudo-random number generator (PRNG)** — an algorithm that, given a starting **seed**, produces a long sequence of numbers that statistically look random. Same seed → same sequence. That property is actually useful (reproducible bugs, repeatable simulations), but it also explains why your first attempt at `rand()` "didn't seem random": same seed every run.

## Key points
- **PRNG basics**: internal state → deterministic function → output number → updated state. The starting state is the **seed**.
- **Statistical quality** matters. A bad PRNG repeats too quickly, has visible patterns when used in pairs, or fails standard tests (TestU01 / dieharder). For games, simulations, ML — care about quality. For cryptography, don't use a PRNG at all; use `<random>`'s cryptographically secure facilities or your OS's CSPRNG.
- **`<cstdlib>`'s `rand()` is bad**. Low period, non-uniform distribution, implementation-defined quality. Avoid in new code.
- **C++11 `<random>`** is the modern interface. It separates concerns cleanly:
  - An **engine** holds state and produces uniform raw bits (`std::mt19937`, `std::mt19937_64`, ...).
  - A **distribution** maps that to the shape you want (`uniform_int_distribution`, `normal_distribution`, ...).
- **Seeding** typically uses `std::random_device` — a non-deterministic source if the platform has one; otherwise a fixed value. Once is enough; don't reseed inside a loop.

## Code in this folder
- `main.cpp` — `<random>`-based die roll, repeated. Demonstrates engine + distribution, and shows what *reproducible* runs look like by also running the same engine with a fixed seed.

## Gotchas
- "I called `rand()` and got the same numbers every run" — that's expected without seeding. Seed once at startup.
- "I seeded inside a loop" — every call resets the sequence and you get the same value or near-duplicates. Seed *once*, then reuse the engine.
- `std::random_device` is allowed to be deterministic on some platforms. For real entropy needs, check `entropy()`.

## Run
    make 8.13
