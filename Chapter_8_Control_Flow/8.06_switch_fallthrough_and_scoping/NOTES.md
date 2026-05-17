# 8.6 — Switch fallthrough and scoping

> learncpp.com: https://www.learncpp.com/cpp-tutorial/switch-fallthrough-and-scoping/

## Why it matters
A `switch` does *not* close out a case the way you'd expect. Without `break`, execution flows straight into the next case — including past the next case label. This is occasionally useful (handling several values with shared logic) and frequently a bug. Since C++17 there's a standard way to mark "yes, I meant that fallthrough": `[[fallthrough]];`. Use it.

A second `switch` quirk is **scope**: cases are *labels*, not blocks. A variable declared in one case is visible in every later case in the same `switch` body, which is almost never what you want and can even crash you if a later case jumps past the initialization.

## Key points
- **Fallthrough** = continuing into the next case because there was no `break`. Three valid use cases for it:
  - Sharing a body across several `case` labels (no statements between them): `case 1: case 2: doX(); break;` — *not* technically fallthrough.
  - Genuinely intending to run case A's body then case B's: mark with `[[fallthrough]];` so readers and the compiler know it's deliberate.
  - Cleanup-on-step style (deinit unwinding). Rare in modern C++; usually a class destructor is better.
- `[[fallthrough]];` (C++17) is a statement attribute. Placed at the end of a case body. Silences `-Wimplicit-fallthrough`.
- **Case scoping**: a `case` is a label inside one big block (the switch body). Variables declared in case A are *visible* in case B but may be **uninitialized** there because the case A initializer was skipped. The compiler errors if a goto-like jump crosses an initialization with a non-trivial type.
- The fix is to **brace each case body**: `case k: { ... }`. Now the variable's scope ends at the closing brace and the next case can't see it.

## Code in this folder
- `main.cpp` — deliberate fallthrough with `[[fallthrough]]`, multi-label cases (not fallthrough), and the scoping fix with `{}` around a case body.

## Gotchas
- `[[fallthrough]];` requires a **semicolon** — it's an attribute on a *null statement*. `[[fallthrough]] case 2:` is wrong.
- An unbraced case with `int n = 5;` may not even compile if a later case can be reached without going through this one (initialization-crossing jump). Brace the case and the error disappears.
- "Empty" fallthrough (`case 1: case 2: doX(); break;`) is universally understood; it doesn't need `[[fallthrough]]`. The attribute is for when there are *statements* in the falling-through case.

## Run
    make 8.06
