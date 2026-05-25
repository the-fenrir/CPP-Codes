# 18.4 — Timing your code

> learncpp.com: https://www.learncpp.com/cpp-tutorial/timing-your-code/

## Why it matters
"Is version A faster than B?" only has an honest answer if you measured. Gut feel about performance is famously wrong — small changes can be 10× faster or 10× slower than you'd guess. `<chrono>` gives you a portable clock; wrapping it in a tiny `Timer` class makes "time this block" a two-line addition.

## Key points
- **`std::chrono::steady_clock`** is the right default for benchmarks: monotonic (never goes backward), unaffected by wall-clock adjustments. Use `system_clock` only when you need calendar time.
- **The pattern**: snapshot `now()` before, snapshot `now()` after, subtract, cast to a duration you can read (`duration<double>` for seconds, `milliseconds`, etc.).
- **Encapsulate it**: a `Timer` class that captures `start = now()` in its constructor and exposes `elapsed()` is reusable and removes ceremony at the call site.
- **Debug vs. release**: optimized builds are *dramatically* faster. Always benchmark with optimizations (`-O2`/`-O3`); debug numbers don't reflect what users see.
- **Compare, don't quote absolutes**: "version B took 0.6× as long as version A" is portable; "version B took 12ms" is not.
- **Discipline**: run multiple times, watch the variance, close other apps, re-measure the baseline at the end to confirm your machine didn't change underfoot.
- **Watch for the optimizer deleting your benchmark**: if a result isn't used, the compiler may eliminate the loop entirely. Print or `volatile`-store the result to keep it honest.

## Code in this folder
- `main.cpp` — a `Timer` class plus a head-to-head benchmark: hand-rolled selection sort (from 18.01) vs. `std::sort` on a 10,000-element shuffled vector.

## Gotchas
- This program is intentionally built with `-O0 -g` (the repo's default — see `common/compile_flags.mk`). Numbers here are *not* the numbers you'd see in production. To get release-grade timings, recompile with `-O2`.
- `high_resolution_clock` looks tempting but is implementation-defined — on some platforms it's an alias for `system_clock` and can step backward. Stick to `steady_clock`.
- Don't `cout` inside the timed section unless that's what you're measuring — I/O dwarfs almost everything else.

## Run
    make 18.04
