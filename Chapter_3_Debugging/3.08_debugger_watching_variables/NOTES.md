# 3.8 — Using an integrated debugger: watching variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-an-integrated-debugger-watching-variables/

## Why it matters
Once paused, you need to see state. "Watching" a variable means continuously displaying its current value as you step. It's the difference between "I think `x` is 7" and "I can see `x` is 7." Most semantic bugs are a wrong value at a specific point; the watch window makes that wrong value impossible to miss.

## Key points
- **Locals window** = automatic watch on every variable in the current scope. Almost always what you actually want — it's free, you didn't have to set it up.
- **Watch window / watch expression** = an arbitrary expression evaluated and shown at every pause. Useful for values that aren't a single variable: `a + b`, `arr[i]`, `*ptr`, `static_cast<int>(c)`.
- A watched **expression** with side effects is evil (`++i` in a watch increments `i` every time the debugger pauses). Stick to pure expressions.

`lldb` / `gdb` cheat sheet:

| Action                          | lldb                              | gdb                       |
|---------------------------------|-----------------------------------|---------------------------|
| Print one variable              | `p x`                             | `p x`                     |
| All locals in current frame     | `frame variable` / `fr v`         | `info locals`             |
| Print with format               | `p/x x` (hex), `p/t x` (binary)   | `p/x x`, `p/t x`          |
| Pretty-print STL containers     | usually automatic                  | `p *v._M_impl._M_start@v.size()` (or `set print pretty on`) |
| Persistent watch expression     | `display x` (re-prints at each stop) | `display x`            |
| Stop watching                   | `undisplay 1`                     | `undisplay 1`             |
| **Data watchpoint** (break when value *changes*) | `watch set variable x` | `watch x`        |

- The watchpoint (last row) is the killer feature: "stop the program the moment `x` becomes 0." Lets you find *who* corrupted a value without knowing where it happens.

## Code in this folder
- `main.cpp` — accumulates a running sum *and* a running product over a list, with a bug that corrupts the product. Use `display product` so you can watch it tick through values; you'll see the moment it goes wrong.

## Gotchas
- Watchpoints on stack variables only live as long as that stack frame. Cross a function boundary and the watchpoint silently disappears (lldb/gdb warn, sometimes).
- A watched expression is re-evaluated on every stop — if it dereferences a pointer that became null mid-debug, the debugger itself can crash. Use `p` ad-hoc rather than `display` for risky expressions.

## Run
    make 3.08
