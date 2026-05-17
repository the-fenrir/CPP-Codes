# 1.8 — Whitespace and basic formatting

> learncpp.com: https://www.learncpp.com/cpp-tutorial/whitespace-and-basic-formatting/

## Why it matters
The compiler doesn't care about indentation or blank lines. Humans do. Consistent formatting is the cheapest readability win in any codebase — and your future self counts as one of those humans.

## Key points
- C++ is mostly whitespace-insensitive. `int x{5};` and `int   x  {  5 }  ;` mean the same thing.
- Exceptions: tokens must be separated where ambiguity would otherwise arise (`int x` needs a space between `int` and `x`), and inside string literals whitespace is preserved.
- **Conventions worth adopting on day one:**
  - One statement per line.
  - Indent the body of every block consistently (this repo uses 4 spaces).
  - Always use `{}` braces around the body of `if`/`for`/`while`, even single-statement bodies.
  - Put `{` and `}` on their own lines (Allman) *or* `{` at end of line (K&R) — pick one and never mix.
  - Keep lines under ~80–100 chars.

## Code in this folder
- `main.cpp` — the same logic formatted well and formatted badly.

## Gotchas
- Tab-vs-space wars are real; configure your editor and a `.editorconfig` so it's not a recurring per-commit problem.
- "Brace-elided" `if` statements (no `{}`) are the source of the infamous Apple `goto fail` bug. Just always brace them.

## Run
    make 1.08
