# Chapter 9 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-9-summary-and-quiz/

## One-page recap

### Testing & coverage (9.1–9.2)
- **Unit test** = tests one function in isolation. **Integration test** = tests how units cooperate.
- Cheap automation beats expensive frameworks beats manual testing. A `main()` that prints PASS/FAIL is a real test framework.
- **Coverage** types: *statement* < *branch* < *loop (0/1/2)*. Coverage tells you what *ran*, not what's *correct* — assertions still have to do the verifying.
- Test boundaries, not centers: 0, 1, many; min, max, just-past; empty input.

### Semantic errors (9.3)
- Compiles ≠ correct. The classic offenders: integer division, off-by-one, `=` vs `==`, operator precedence, signed/unsigned mixing, uninitialized reads, floating-point equality, missing `break`.
- `-Wall -Wextra -Wpedantic` catches a big chunk of these. Turn warnings on, treat them as errors.

### Detecting & handling errors (9.4)
- **Precondition / invariant / postcondition** — name the contract before writing the body.
- **Recoverable** errors (bad input, missing file, network hiccup) ⇒ return an error value, retry, or throw.
- **Non-recoverable** errors (broken invariant, corrupted state) ⇒ `assert` / `abort`.
- Modern default for a recoverable error: `std::optional<T>` or an exception. Avoid magic sentinels (`-1`) when `T`'s range is unconstrained.
- Diagnostics go to **`std::cerr`** (unbuffered, separately redirectable), not `std::cout`.

### `std::cin` and invalid input (9.5)
- After a failed `>>`: `cin.clear()` to reset flags, **then** `cin.ignore(max, '\n')` to drop the bad bytes. One without the other doesn't recover.
- After a successful `>>`: still `ignore(max, '\n')` to flush trailing junk on the same line.
- Wrap the read in a `while (true)` loop and `break` on success.

### `assert` and `static_assert` (9.6)
- **`assert(expr)`** — runtime, compiled out under `NDEBUG`. For *bugs* (impossible states). No side effects inside.
- **`static_assert(expr, msg)`** — compile time, always on. For *compile-time* invariants: type traits, `sizeof`, `constexpr` results.
- `assert` is **not** input validation. If the user can trigger it with a typo, it's the wrong tool.

## Quiz

### Q1 — Hi-Lo with hardened input

Take a simple Hi-Lo game (computer picks a number 1–100; user gets 7 guesses) and make the input layer **robust**. The current version assumes well-behaved input; harden it so all three of these are handled gracefully:

1. **Invalid type** — user types `x` instead of a number. Re-prompt, don't crash.
2. **Out-of-range** — user types `0` or `101`. Reject and re-prompt.
3. **Trailing junk** — user types `43x` or `43 hello`. Accept `43`, silently discard the rest.

Same hardening must apply to the "play again? (y/n)" prompt — `yes please` should be accepted as `y`, `nope` should require re-prompting (or interpret only the first char and flush — designer's call; pick one and stick to it).

**Hint.** Pull the guess-reading logic into a `getGuess(int low, int high)` function so the validation lives in one place. Same idea for `playAgain()`.

## Discussion

### Q2 — Why isn't this a job for `assert()`?

**Question.** Why use stream-state handling + a `while` loop for the Hi-Lo input instead of just `assert(guess >= 1 && guess <= 100)`?

**Answer.** Because bad user input is a *possible* state, not an *impossible* one. The rule from 9.6:

- `assert` is for situations the programmer is *certain* can't happen — broken invariants, logic bugs.
- Error handling (re-prompt, return error value, throw) is for situations the *outside world* can produce.

A user typing `x` or `101` is the outside world doing exactly what users do. An assertion failure aborts the program, gives a stack trace, and is utterly hostile to the user. A retry loop costs the same to write and treats the situation as what it is: routine. Aborting on bad input is also a real-world security pattern to avoid — denial-of-service via malformed input.

### Q3 — Why `std::cerr` for the "invalid input" message and not `std::cout`?

**Answer.** Three reasons:

1. **It's a diagnostic, not output.** `cout` is for the program's *result*. `cerr` is for the program's *complaints*. If someone redirects `cout > out.txt`, they still want to see error messages on the terminal — that only works if errors went to `cerr`.
2. **`cerr` is unbuffered.** If the program later crashes, output already written to `cerr` is on screen; output written to `cout` may still be sitting in a buffer.
3. **Separable redirection.** `./prog 2> errors.log` collects diagnostics without polluting the result stream — only possible because the two streams are distinct.

For an interactive Hi-Lo game the difference is tiny, but the habit is worth forming early.

### Q4 — Why pull `getGuess()` into its own function?

**Answer.** Three reasons, in increasing order of how much they matter:

1. **DRY.** Without it, the clear/ignore/range-check logic gets copy-pasted at every prompt. One copy means one place to fix bugs.
2. **Readability.** `int guess = getGuess(1, 100);` reads as one idea. The inline version reads as "read an int, oh wait check it parsed, oh wait flush the rest, oh wait check the range, oh wait loop." The intent disappears.
3. **Testability.** With the input layer isolated, you can unit-test it (feed a `std::istringstream` to a `getGuess(std::istream&)` overload) without ever running the game. That's the move in `quiz_solutions.cpp` — the I/O loop is parameterised on a stream so tests can script input.

## Run

    make 9.x

`quiz_solutions.cpp` has the worked Hi-Lo with a hardened input layer, plus a scripted test run so the program works under `make` without interactive typing.
