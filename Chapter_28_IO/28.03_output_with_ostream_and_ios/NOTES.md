# 28.3 — Output with ostream and ios

> learncpp.com: https://www.learncpp.com/cpp-tutorial/output-with-ostream-and-ios/

## Why it matters
Every report, every log line, every aligned table you'll ever print is some combination of width, fill, precision, and base. `<iostream>` exposes these via two interfaces that look unrelated but aren't: low-level flags (`setf`/`unsetf`) and high-level manipulators (`std::hex`, `std::setw`, etc.). Knowing which manipulators are *sticky* and which fire only on the next insertion is the single piece of trivia that separates "my output looks right" from "why did everything after row 3 shift one column?".

## Key points
- **Two APIs, same state:**
  - Flag-level: `setf(flag)`, `setf(flag, mask)`, `unsetf(flag)`.
  - Manipulator-level: `std::hex`, `std::dec`, `std::oct`, `std::boolalpha`, `std::fixed`, `std::scientific`, `std::showpos`, etc. — prefer these.
- **Sticky vs. one-shot:**
  - **Sticky** (persist until changed): base (`hex`/`dec`/`oct`), `boolalpha`, `fixed`/`scientific`, `setprecision`, `setfill`, justification (`left`/`right`/`internal`).
  - **One-shot** (apply only to the *next* insertion): `setw` / the `width()` member. After one insertion, width resets to 0.
- **Floating-point precision** has two modes:
  - Default: precision = *significant digits* (default 6).
  - After `std::fixed` or `std::scientific`: precision = *digits after the decimal point*.
- **Justification**: `std::right` (default for numbers), `std::left`, `std::internal` (puts sign on the left, pads the middle — handy for currency/IDs).
- **`put(ch)`** writes a single character; **`write(buf, n)`** writes a raw byte sequence (binary-mode partner of `read`).
- **`flush()`** forces the buffer out without inserting `'\n'`. `std::flush` is the manipulator form.

## Code in this folder
- `main.cpp` — prints the same table of numbers under several formatting regimes and demonstrates the sticky/one-shot distinction explicitly.

## Gotchas
- **`setw` resets after one insertion.** If you want every column to be width 10, you write `std::setw(10)` before *every* value. Forgetting this is the #1 alignment bug.
- **`std::fixed` changes the meaning of precision.** Set them together (`std::fixed << std::setprecision(2)`), don't assume the previous `setprecision` still means what it did.
- Once you set `std::boolalpha` or `std::hex`, it stays set. If a function changes stream state, save and restore (`std::ios::fmtflags old = cout.flags(); ... cout.flags(old);`) — otherwise callers downstream see garbage.

## Run
    make 28.03
