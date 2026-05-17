# 9.2 — Code coverage

> learncpp.com: https://www.learncpp.com/cpp-tutorial/code-coverage/

## Why it matters
"I tested it" is ambiguous. *Coverage* makes it concrete: what fraction of the code did the test suite actually execute? Coverage isn't a goal by itself — 100% coverage with weak assertions is worthless — but it's a fast way to find code that *no test exercises at all*. Untouched code is unverified code.

## Key points
- **Statement coverage** — percentage of statements executed at least once. The weakest useful flavor.
- **Branch coverage** — percentage of branches taken in both directions. `if (cond)` counts as two branches: condition true *and* condition false. Strictly stronger than statement coverage.
- **Loop coverage (the 0/1/2 test)** — for each loop, prove it works when it iterates 0 times, 1 time, and 2+ times. Catches "off-by-one when empty" and "second iteration overwrites first" bugs that 1-iteration tests miss.
- **Boundary testing** — at the edges of valid input ranges: min/max, empty/singleton/non-empty, just-below/at/just-above any threshold.
- High coverage ≠ correct. It only means the lines *ran*. Assertions must still check something.

## Code in this folder
- `main.cpp` — a `classify(int)` function with three branches, exercised by a test table that hits each branch *and* the 0/1/2 case for a loop helper. Comments mark exactly which test covers which branch.

## Gotchas
- **Coverage tools lie about short-circuited expressions.** `if (a && b)` may show "fully covered" even though `b` was never evaluated, because `a` was false every time. Test the `b`-only side explicitly.
- **A test that hits the branch but doesn't assert anything is a free coverage point and zero bug-finding.** Coverage measures *exercise*, not *verification*.
- **Don't chase 100%.** The last 5% is often defensive code (`default:`, "this can't happen" branches). Chasing it usually means deleting useful defenses to please the metric.

## Run
    make 9.02
