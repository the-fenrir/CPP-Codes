# 12.13 — In and out parameters

> learncpp.com: https://www.learncpp.com/cpp-tutorial/in-and-out-parameters/

## Why it matters
Function parameters fall into three roles: **in** (function reads), **out** (function writes), **in/out** (function reads and writes). Choosing the right parameter mechanism for each role is most of what good signature design comes down to.

## Key points
- **In parameter** — function reads only. Mechanism: pass by value (small types) or `const T&` (large/non-trivial types).
- **Out parameter** — function writes only. Mechanism: prefer **return by value** (with multiple values, use `std::tuple`, `std::pair`, or a small struct). Out-parameter syntax (`T&` or `T*`) is a fallback.
- **In/out parameter** — function reads and writes. Mechanism: `T&` (or `T*` if absence is meaningful).
- Modern guidance: **prefer return-by-value over out-parameters.** Copy elision makes return free; the call site reads naturally (`auto x = compute();`).
- Out parameters force "default-construct, then mutate," which doesn't compose and breaks `const`.

## Code in this folder
- `main.cpp` — same computation written as out-parameter, return-by-value, and struct-of-multiple-returns. Compare call sites.

## Gotchas
- Out parameters can't return objects that aren't default-constructible. Return-by-value can.
- Mixing in and out in the same parameter list often signals "this function does two things" — consider splitting.
- `[[nodiscard]]` on the return type forces the caller to use it. Use it for any function whose return value matters.
- Boolean out-parameter + bool return (`bool tryParse(string, int& out)`) is a legitimate idiom — but `std::optional<int>` (12.15) is usually cleaner.

## Run
    make 12.13
