# Chapter 4 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-4-summary-and-quiz/

## One-page recap

### Bits, bytes, types (4.1, 4.3)
- Bit = 0/1; byte = 8 bits (everywhere you care about); memory is byte-addressable.
- A **type** tells the compiler how to interpret a chunk of memory. Same bits, different type = different value.
- `sizeof(T)` returns size in bytes. `sizeof(char) == 1` always; everything else has only a minimum.

### Void (4.2)
- `void` = "no type." Valid as a function return type; cannot be the type of a variable. Empty parameter list is `f()`, not `f(void)`.

### Signed integers (4.4)
- `short`, `int`, `long`, `long long`. Prefer the short form (no `int` suffix, no `signed` prefix).
- Range of *n* bits: −2^(n−1) … 2^(n−1) − 1.
- **Signed overflow is undefined behavior.** Not "wraps negative" — UB.
- Integer division truncates toward zero. `8 / 5 == 1`. Mix with a `double` to get fractional results.

### Unsigned integers — and why to avoid them (4.5)
- Modular wrap-around is well-defined but silent. `0u − 1` is `UINT_MAX`.
- Mixing signed and unsigned in one expression converts the signed value to unsigned. `-1 < 1u` is `false`.
- Best practice: **signed for quantities**. Unsigned only for bit manipulation, intentional wrap, and unavoidable size types.

### Fixed-width integers and `size_t` (4.6)
- `<cstdint>`: `std::int8_t` … `std::int64_t` and unsigned counterparts. Exact widths.
- `std::int8_t` / `std::uint8_t` typically alias `signed char` / `unsigned char` — they **print as characters**. Cast to `int` to print numerically.
- `std::size_t` (from `<cstddef>`) is the unsigned type used for sizes / indices in the standard library. Width matches the address space.

### Scientific notation (4.7)
- C++ literal form `1.6e-19`. Internally how floats are stored.
- Normalized form has exactly one non-zero digit before the decimal point.

### Floating point (4.8)
- `float` ≈ 7 sig figs, `double` ≈ 16, `long double` platform-dependent. **Default to `double`.**
- A floating literal is `double` by default; suffixes are `f` (float) and `L` (long double).
- `std::setprecision` controls how many digits are printed. Sticky.
- `0.1 + 0.2 != 0.3`. Never `==` floats.
- `1.0 / 0.0` is `+Inf`. `sqrt(-1.0)` is `NaN`. `NaN != NaN`. Test with `std::isnan`.

### Bool (4.9) and if statements (4.10)
- `bool`: `true` / `false`, stored as `1` / `0`. `std::boolalpha` prints / reads as text.
- `if (condition) … else …`. Non-zero converts to `true`. Use braces on every branch. Predicate functions plug into `if`.

### Chars (4.11)
- 1 byte. ASCII numeric code. Single quotes (`'A'`) for char literals; double quotes (`"A"`) for string literals.
- `std::cout << ch` prints the character; `static_cast<int>(ch)` prints the number.
- Escape sequences: `'\n'`, `'\t'`, `'\\'`, `'\''`, `'\"'`, `'\0'`.

### Type conversion and `static_cast` (4.12)
- Implicit conversions happen at calls / assignments / mixed-type expressions.
- Narrowing conversions are rejected by brace-initialization.
- `static_cast<T>(expr)`: explicit, type-checked conversion. Takes responsibility for any loss.
- The canonical use: print a `char` (or `std::int8_t`) as a number — `static_cast<int>(ch)`.

---

## Quiz

### Q1 — Picking the right type

For each scenario, name the data type you'd use. Brief justification each.

- **a)** The age of the user in years (size unimportant).
- **b)** Whether the user wants the app to check for updates.
- **c)** The value of π to many decimal places.
- **d)** The number of pages in a textbook (size unimportant).
- **e)** The length of a couch in feet, to 2 decimal places (size matters).
- **f)** How many times you've blinked since you were born (millions).
- **g)** A menu selection by letter.
- **h)** Your year of birth (size matters).

**Answers (used in `quiz_solutions.cpp`):**

| | Scenario | Type | Reason |
|---|---|---|---|
| a | Age (size unimportant) | `int` | Quantities → signed. Size doesn't matter → default `int`. |
| b | Yes/no | `bool` | Two-value answer. |
| c | π | `double` | Real number, default float type. `float` loses precision past ~7 digits. |
| d | Page count (size unimportant) | `int` | Same reasoning as (a). |
| e | Length in feet (size important, 2 dp) | `float` | Real number; tightness on size means we deliberately accept `float`'s ~7 digits. Use `double` if in doubt. |
| f | Lifetime blinks (millions, possibly billions) | `std::int32_t` or `long long` | Beyond a 16-bit short's range; `int` is usually fine but pinning to a fixed width makes the assumption explicit. |
| g | Letter selection | `char` | Single character. |
| h | Birth year (size important) | `std::int16_t` | A 16-bit signed int holds −32768..32767 — fits any plausible birth year and pins the width. |

### Q2 — Calculator

Write a program that reads two `double`s and an operator (`+`, `-`, `*`, `/`) and prints the result. Invalid operators produce no output.

Expected interaction:
```
Enter a double value: 6.2
Enter a double value: 5
Enter +, -, *, or /: *
6.2 * 5 is 31
```

The quiz_solutions.cpp version runs in a non-interactive form (reading from a hard-coded `std::istringstream`) so `make 4.x` produces deterministic output. Replace the stream with `std::cin` for the real interactive version.

### Q3 (extra credit) — Falling-ball simulation

Ask the user for the height of a tower in meters. Then, for each of seconds 0 through 5, compute the height of a ball dropped from that tower at that time, using `distance_fallen = 9.8 * t * t / 2`. If the ball has reached the ground (`height ≤ 0`), print "At N seconds, ball is on the ground."

Use a separate function `calculateHeight(double towerHeight, int seconds)` that returns the ball's current height (≥ 0 — clamp to zero if it's already on the ground), and a printer that uses it.

Expected output for tower height 100:
```
At 0 seconds, the ball is at height: 100 meters
At 1 seconds, the ball is at height: 95.1 meters
At 2 seconds, the ball is at height: 80.4 meters
At 3 seconds, the ball is at height: 55.9 meters
At 4 seconds, the ball is at height: 21.6 meters
At 5 seconds, the ball is on the ground.
```

(The numbers shift if you start from a different tower height.)

## Run

    make 4.x

`quiz_solutions.cpp` contains:
- **Q1**: typed declarations with a comment on each one.
- **Q2**: a `calculate` function and a `main` that drives it with a fixed input stream so the output is reproducible.
- **Q3**: `calculateHeight` + `printBallHeight`, driven by a fixed tower height of 100 m.
