# 8.11 — Break and continue

> learncpp.com: https://www.learncpp.com/cpp-tutorial/break-and-continue/

## Why it matters
`break` and `continue` are how you bend a loop's control flow without rewriting its head. `break` exits the enclosing loop or `switch` immediately. `continue` jumps to the next iteration — i.e., skips the rest of the body but still runs the loop's step and condition check. Used judiciously, they make a loop body read like its intent ("skip the empty lines, stop at EOF"); used carelessly, they hide the actual termination condition.

## Key points
- `break;` — exit the **innermost** enclosing `for`/`while`/`do-while`/`switch`. C++ has no `break 2;` — to break out of nested loops, refactor into a function with `return` or use a flag.
- `continue;` — skip the rest of the current iteration. In a `for` loop, the **step still runs** before the next condition check. In a `while`, the condition is checked immediately. (This bites people: a `continue` inside `while (i < n) { ...; ++i; }` that comes *before* `++i` can loop forever.)
- `return;` from inside a loop exits the whole function — strictly stronger than `break`.
- Style: a single early `break`/`continue` near the top of the body (guard clauses) tends to read well; multiple scattered through the body do not. If you find yourself with three `break`s and two `continue`s, the loop probably wants to be split.

## Code in this folder
- `main.cpp` — `break` to stop a search, `continue` to skip values, the `while + continue` infinite-loop trap shown commented out, and a nested-loop `break` that *only* exits the inner loop.

## Gotchas
- `break` in a `switch` inside a loop breaks the **switch**, not the loop. Caught most often when refactoring an `if/else` into a `switch` inside a loop.
- `continue` in a `for` will *still* execute the step. In a `while`, you're responsible for incrementing yourself — easy to forget after a `continue`.
- "Just one more `break`" is almost always a sign the loop's exit condition is hiding in the body. Try moving it back into the header (`while (cond1 && cond2)`).

## Run
    make 8.11
