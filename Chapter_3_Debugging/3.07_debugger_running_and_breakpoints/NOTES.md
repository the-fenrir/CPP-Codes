# 3.7 — Using an integrated debugger: running and breakpoints

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-running-and-breakpoints/

## Why it matters
Stepping (3.6) from `main` to a bug 10,000 lines in is unusable. **Breakpoints** let you say "pause here," then `run` the program at full speed until it hits that point. Combined with **run-to-cursor** and **continue**, you go from a 5-minute manual step-through to a 5-second jump to the interesting spot.

## Key points
- **Breakpoint** = a marker on a line; execution halts when that line is about to execute.
- **Run** = start the program (or restart it after a change).
- **Continue** = resume from the current pause; stop again at the next breakpoint or program end.
- **Run-to-cursor** = "continue, but stop at *this* line whether or not it has a breakpoint."
- **Conditional breakpoints**: "break here only if `i == 47`." Invaluable for "bug only happens on the millionth iteration."

`lldb` / `gdb` cheat sheet for a `-g` binary built by this repo:

| Action                  | lldb                          | gdb                          |
|-------------------------|-------------------------------|------------------------------|
| Break on a function     | `b funcName`                  | `b funcName`                 |
| Break on file:line      | `b main.cpp:42`               | `b main.cpp:42`              |
| Conditional break       | `breakpoint set -f main.cpp -l 42 -c 'i==47'` | `b main.cpp:42 if i==47` |
| List breakpoints        | `br list`                     | `info b`                     |
| Delete a breakpoint     | `br del 1`                    | `d 1`                        |
| Run                     | `run`                         | `run`                        |
| Continue                | `c`                           | `c`                          |
| Run to here             | (set break, then `c`)         | `tbreak main.cpp:42 ; c`     |

- A breakpoint *survives* program restarts within the same debugger session — that's the loop you want: edit code outside, recompile, `run` again, debugger stops at the same breakpoint.

## Code in this folder
- `main.cpp` — a `binarySearch` with a bug that only manifests on the search-not-found path. Set a conditional breakpoint that fires only when the target is missing, then step through. The buggy case is `binarySearch(arr, 42)` — `42` is not in the array.

## Gotchas
- Breakpoints set on lines with no executable code (blank lines, `}`, comments) silently slide to the next real line. If your breakpoint "doesn't fire," check it's actually on a statement.
- Conditional breakpoints with expensive conditions slow down the program massively. Use a sentinel variable in the code if the condition fires millions of times.

## Run
    make 3.07
