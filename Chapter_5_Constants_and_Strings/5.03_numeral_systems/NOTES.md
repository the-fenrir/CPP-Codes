# 5.3 — Numeral systems (decimal, binary, hex, octal)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/numeral-systems-decimal-binary-hexadecimal-and-octal/

## Why it matters
The number `255` is the same value as `0xFF` is the same value as `0b11111111` is the same value as `0377`. What changes is how *readable* the code is at a glance. Bit-flag constants written in decimal are unreadable; in hex or binary they're trivial. Knowing the prefixes also means you stop tripping over the silent-octal trap.

## Key points
- **Decimal** — default. `42`.
- **Octal** — leading `0`. `0377` is decimal 255. Almost never what you want; the silent trap is `int x{ 09 };` → error (`9` isn't an octal digit) when you meant nine.
- **Hex** — `0x` or `0X` prefix, digits `0-9a-fA-F`. `0xFF` is 255. Standard for memory addresses, bit masks, color values.
- **Binary** (C++14) — `0b` or `0B` prefix. `0b1010'0001`. Use digit separators to group nibbles; it's the only thing keeping long binary literals legible.
- **Output base** is controlled by stream manipulators: `std::dec`, `std::hex`, `std::oct`. They're *sticky* — once set, every subsequent integer prints in that base until you change it back.
- No built-in `std::bin` manipulator. Use `std::bitset<N>` (`#include <bitset>`) for binary output, or print nibbles by hand.

## Code in this folder
- `main.cpp` — same value written four ways, sticky manipulators, and `std::bitset` for binary output.

## Gotchas
- Leading `0` ≠ "decimal with padding." `010` is *eight*, not ten. Bites people copying ZIP codes or PIDs into source.
- `std::hex` stays on. After `std::cout << std::hex;`, the *next* integer also prints in hex. Reset with `std::cout << std::dec;` (or scope it).
- Hex / binary literals are still just integers — they have a normal integer type (`int` by default), and overflow / sign rules apply. `0xFFFFFFFF` doesn't fit in a 32-bit `int`; it becomes `unsigned int`.

## Run
    make 5.03
