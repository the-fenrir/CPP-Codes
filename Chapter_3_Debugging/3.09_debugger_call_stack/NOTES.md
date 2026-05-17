# 3.9 — Using an integrated debugger: the call stack

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-the-call-stack/

## Why it matters
"How did execution get here?" The **call stack** answers that question — it's the chain of unfinished function calls from `main` down to the current line. When a function misbehaves, the bug is often not in the function itself but in *the caller* that passed it bad arguments. The call stack is how you find that caller.

## Key points
- Every active function call has a **stack frame**: its parameters, local variables, and the return address. The call stack is the stack of those frames.
- When the debugger pauses, you can:
  - **Print the stack** — see the full chain `main → a → b → c` with file:line for each.
  - **Switch frames** — jump to a caller's frame and inspect *its* variables, even though you're not "in" it.
- This is invaluable for assertions, segfaults, or any pause: "the crash is in `c`, but who called `c`? With what arguments?"

`lldb` / `gdb` cheat sheet:

| Action                       | lldb                | gdb                |
|------------------------------|---------------------|--------------------|
| Print the call stack         | `bt` / `thread backtrace` | `bt` / `where`    |
| Print stack with locals      | `bt all`            | `bt full`          |
| Switch to frame N            | `frame select N` / `f N` | `frame N` / `f N` |
| Up one frame (toward caller) | `up`                | `up`               |
| Down one frame               | `down`              | `down`             |
| Inspect current frame's vars | `frame variable`    | `info locals` / `info args` |

- A crash without a debugger gives you nothing. A crash *in* a debugger gives you `bt` — the call stack at the moment of death. Run unfamiliar crashes under `lldb`/`gdb` even if you don't plan to step.

## Code in this folder
- `main.cpp` — mirrors the quiz problem (Q3): `main → a → b → c` and `b → d`, with a deliberate `std::abort()` inside `d` so you can run it under the debugger and read the stack.
  ```
  lldb build/3.09/main
  (lldb) run
  Process N stopped: SIGABRT
  (lldb) bt
  ```

## Gotchas
- Tail-call optimization or inlining can drop frames from the stack. Always debug with `-O0`, which preserves every call.
- Reading the stack on a corrupted-stack crash (buffer overrun, bad function pointer) can show nonsense frames — the symptom isn't in the source, it's that the bookkeeping itself is wrecked. That's the moment to reach for `valgrind` or `-fsanitize=address`.

## Run
    make 3.09
