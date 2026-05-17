# 6.3 — Remainder and exponentiation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/remainder-and-exponentiation/

## Why it matters
`%` is how you "ask the question" — divisibility, periodicity, even/odd, wrap-around. Easy, until negative operands show up: `-5 % 2` is `-1`, not `1`, so the classic `x % 2 == 1` check for odd silently breaks. And C++ has no exponent operator — you reach for `std::pow`, which is a double-precision function. For integer exponents that's usually wrong.

## Key points
- **Remainder `%`** is integer-only in C++ (`fmod`/`std::fmod` for floats).
- Sign of `a % b` follows the sign of `a`. `-5 % 2 == -1`. Test parity with `x % 2 != 0`, not `== 1`.
- `%` and `/` are siblings: `a == (a / b) * b + (a % b)`.
- **No `^` exponent operator.** `^` is bitwise XOR. `2 ^ 3` is `1`, not `8`.
- `std::pow(base, exp)` from `<cmath>` works in `double`. Precision loss for big integer answers — `std::pow(10, 18)` may not be exactly `1000000000000000000`.
- For integer exponentiation, write your own: exponentiation by squaring, or just multiply in a loop for small exponents. Watch for overflow.

## Code in this folder
- `main.cpp` — `%` with negatives, the parity bug, `std::pow` precision, and a hand-rolled `intPow`.

## Gotchas
- "`a % b == 1` means odd" — only when `a >= 0`. Use `a % 2 != 0`.
- `int n = std::pow(10, 3);` may store `999` on some implementations because of double rounding. Round explicitly, or use an integer routine.
- `^` for exponentiation is the single most common C++ syntax error from people coming from Python/Matlab/spreadsheets.

## Run
    make 6.03
