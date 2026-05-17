# 3.4 — Basic debugging tactics

> learncpp.com: https://www.learncpp.com/cpp-tutorial/basic-debugging-tactics/

## Why it matters
Before you reach for a debugger, two cheap tactics resolve the majority of bugs in under a minute: **comment things out** and **print things**. The whole "advanced" debugger chapter (3.6–3.9) is what you escalate to when these stop being enough.

## Key points
- **Comment out half the code.** If the bug disappears, it's in the commented half; if not, it's in the uncommented half. Binary search applied to source code. Especially useful when the crash is "somewhere in this 200-line function."
- **Validate that code is running.** Drop a `std::cout << "in foo\n";` at the entry of a function you *think* is being called. Half the time you'll discover the path you assumed isn't the path being taken.
- **Print variable values.** At suspicious points, print what you've got: `std::cout << "x=" << x << " i=" << i << '\n';`. Aim to print at decision points (loop conditions, branches), not random lines.
- **Tag your prints.** Prefix with `>>>` or `[DBG]` so they're obvious in output and easy to grep+delete later. Otherwise they ship to production.
- **Keep prints separate from real output.** This is what `std::cerr` is for (next lesson) — `cerr` is unbuffered so prints survive a crash, and it's separable on the command line via `2>` redirection.

## Code in this folder
- `main.cpp` — a "process a list" function with a real bug, instrumented with `[DBG]`-tagged prints showing the technique. Comment out the print lines once you've found the bug; that's the workflow.

## Gotchas
- Prints that *aren't* flushed can be lost on crash. `std::cout` is line-buffered to a terminal but fully buffered if redirected. Use `std::cerr` (unbuffered) or `<< std::flush` / `<< std::endl` for crash-survival prints.
- Print-debugging changes timing. A bug that depends on race conditions or buffer sizes can vanish when you add prints (a "Heisenbug"). For those, you need a real debugger.

## Run
    make 3.04
