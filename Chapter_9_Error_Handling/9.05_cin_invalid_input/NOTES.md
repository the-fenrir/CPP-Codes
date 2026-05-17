# 9.5 — `std::cin` and handling invalid input

> learncpp.com: https://www.learncpp.com/cpp-tutorial/stdcin-and-handling-invalid-input/

## Why it matters
`std::cin >> x` looks innocent until the user types `abc` into an `int` prompt. The stream silently enters a failed state, `x` is left untouched, and every subsequent `>>` is a no-op. Most beginner programs are wrong here. The fix is mechanical but easy to skip, so it's worth burning into muscle memory.

## Key points
**The four failure modes of `std::cin >> x`:**
1. **Extraneous input** — user types `5 abc`. The `5` is consumed; `abc` sits in the buffer and contaminates the next read.
2. **Wrong type** — user types `abc` into an `int >>`. Extraction fails; `cin` goes into fail state; the variable is untouched (and in pre-C++11, was zeroed; since C++11 it's set to 0 on extraction failure, but the stream is *still* in fail state).
3. **Out-of-range** — user types `99999999999`. Extraction fails with overflow; variable is clamped to the type's max/min; stream goes to fail state.
4. **Nothing entered (EOF)** — extraction fails; stream goes to `eofbit`.

**The fix — the three-line dance:**
```cpp
if (!std::cin) {              // entered fail state?
    std::cin.clear();         //   reset the flags
    std::cin.ignore(...);     //   discard the bad input from the buffer
}
std::cin.ignore(...);         // also flush trailing junk on success
```

**`std::cin.ignore(N, '\n')`** — discard up to `N` chars or up to (and including) a newline, whichever comes first. Common idiom: `std::numeric_limits<std::streamsize>::max()`.

**Loop until valid:** wrap the read in a `while (true) { read; if (ok) break; }`.

## Code in this folder
- `main.cpp` — reads an `int` from a **`std::istringstream`** seeded with scripted input (so the program runs non-interactively, suitable for `make`). Demonstrates the full clear/ignore/retry loop on three failure modes: junk text, valid + trailing junk, and out-of-range.

## Gotchas
- **`std::cin.ignore()` with no args** ignores exactly one character — rarely what you want.
- **`std::cin.clear()` does not flush the buffer.** It only resets the error flags. You still need `ignore()` to drop the bad bytes.
- **Mixing `>>` and `std::getline()`** is a classic trap: `>>` leaves the newline in the buffer, and the next `getline()` reads an empty string. Always flush after `>>` if a `getline` is coming.

## Run
    make 9.05
