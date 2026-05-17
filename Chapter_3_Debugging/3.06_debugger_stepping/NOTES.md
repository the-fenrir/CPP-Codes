# 3.6 — Using an integrated debugger: stepping

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-stepping/

## Why it matters
The debugger is a time machine for your program: pause execution at a line, look at every variable, then advance one statement at a time. **Stepping** is the basic verb. Once you internalize step-over vs. step-into vs. step-out, you stop guessing what code does and start watching it do the thing.

## Key points
The chapter uses Visual Studio / Code::Blocks. The equivalents in `lldb` (macOS) and `gdb` (Linux) for a binary compiled with `-g` (which this repo does):

| Concept           | What it does                              | lldb       | gdb     |
|-------------------|-------------------------------------------|------------|---------|
| **Step into**     | If next stmt is a call, enter the callee  | `step` / `s` | `step` / `s` |
| **Step over**     | Execute next stmt; if it's a call, run it to completion without entering | `next` / `n` | `next` / `n` |
| **Step out**      | Run until the current function returns    | `finish`   | `finish` |
| **Step instruction** | One machine instruction (rare in C++)   | `si` / `ni` | `si` / `ni` |

- **Step into** when you suspect a callee is wrong (or you've never looked at it).
- **Step over** when you trust a callee and just want to see its result.
- **Step out** when you accidentally stepped into something boring (like a `std::vector` constructor) and want back to your code.
- All three preserve program state — variables, the call stack, output so far. They differ only in *where they stop*.

## Code in this folder
- `main.cpp` — `sumDigits(n)` is supposed to return the digit sum (`123 → 6`). It returns the wrong value due to an off-by-one in the loop. Build with `make 3.06`, then debug it:
  ```
  lldb build/3.06/main           # macOS
  (lldb) b sumDigits             # break on entry
  (lldb) run
  (lldb) n                       # step over, line by line
  (lldb) frame variable          # see all locals
  ```
  Watch `n` and `sum` after each step; you'll see exactly where the math goes wrong.

## Gotchas
- Stepping with optimizations on (`-O2`) lies — the debugger jumps around as the compiler reorders statements. Always debug with `-O0 -g`, which this repo's Makefile already sets.
- "Step into" a standard-library call drops you into header soup. Use "step out" to escape quickly.

## Run
    make 3.06
