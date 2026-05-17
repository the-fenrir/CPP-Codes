# Chapter 8 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-8-summary-and-quiz/

## One-page recap

### Selection (8.2 – 8.7)
- `if` controls **one** statement unless braced. Always-brace style avoids the "added a line and didn't notice" bug.
- `else` binds to the nearest unmatched `if` in the same scope — brace nested ifs to remove the dangle.
- `switch` dispatches on integral values. Each `case` needs a `break` (or `return`) or it falls through. Mark intentional fallthrough with `[[fallthrough]];`. Brace each case body if you declare per-case variables.
- `if constexpr` (C++17) picks a branch at compile time and **discards** the other. Mostly useful in templates where the discarded branch wouldn't compile for the chosen type.
- `goto` exists. You shouldn't write it. The one tempting case ("break out of nested loops") is better solved by extracting a function and using `return`.

### Iteration (8.8 – 8.11)
- `while (cond)` — condition checked at top; may run zero times.
- `do { ... } while (cond);` — body runs first; **always at least one iteration**. Canonical use: input validation.
- `for (init; cond; step)` — counter loop with init/cond/step collocated. Range-based `for (auto& e : v)` when you don't need the index.
- `break` exits the innermost `for`/`while`/`do`/`switch`. `continue` skips to the next iteration (and runs the `for` step, but **not** any manual increment in a `while`).

### Halts (8.12)
- Returning from `main` is the only "clean" exit — full destructor unwinding + atexit + stream flush.
- `std::exit` runs atexit handlers + static destructors but **not** local destructors. Don't call from a function that owns RAII resources.
- `std::abort` runs nothing. `assert` uses it on failure. Almost never the right intentional exit.

### Randomness (8.13 – 8.15)
- `<random>` separates engines (state + raw uniform bits) from distributions (target shape). `mt19937` is the everyday default.
- Seed **once** with `std::random_device`. Don't reseed inside loops.
- A program-wide engine (an `inline` namespace global, or `static` inside a helper) is the right scope for most apps. learncpp.com's `Random.h` is exactly this pattern — inlined here in 8.15 so each lesson stays standalone.

## Quiz

### Q1 — Ball-drop simulation with a `while` loop

The original ball-drop program ran for exactly 5 seconds. **Modify it** so the ball falls for as many seconds as it actually needs to reach the ground — i.e., the loop continues until `calculateAndPrintBallHeight()` reports the ball has hit the ground.

Use:
- a `constexpr` for the gravity acceleration (9.8 m/s²),
- a namespace to group the simulation helpers,
- `0.0` as the "on the ground" terminating value returned by the helper.

Expected behaviour: drop from 100 m, print height each second, loop until height is at the ground, then announce.

### Q2 — `isPrime` with a `for` loop

Write `bool isPrime(int x)` such that the program below compiles and the assertions all pass:

```cpp
#include <cassert>

int main()
{
    assert(!isPrime(0));
    assert(!isPrime(1));
    assert( isPrime(2));
    assert( isPrime(3));
    assert(!isPrime(4));
    assert( isPrime(5));
    assert( isPrime(7));
    assert(!isPrime(9));
    assert( isPrime(11));
    assert( isPrime(13));
    assert(!isPrime(15));
    assert( isPrime(13417));   // big one
    return 0;
}
```

**Extra credit:** only test divisors up to `sqrt(x)`, and skip even divisors after checking 2.

### Q3 — Hi-Lo guessing game

Write a Hi-Lo game:
- the program picks a random integer in `[1, 100]`,
- the user has **7 tries** to guess it,
- after each wrong guess, say "too high" or "too low",
- when the user wins or loses, ask "play again?" — accept `y`/`n` only (re-prompt on anything else).

Use `<random>` (this repo doesn't have the site's `Random.h`; same trick as in 8.15 — inline a tiny `Random` namespace at the top of the file).

The quiz solution simulates user input from a fixed array so the build is reproducible (no `std::cin` blocking).

## Run

    make 8.x

`quiz_solutions.cpp` has worked code for all three problems with design commentary.
