# 1.2 — Comments

> learncpp.com: https://www.learncpp.com/cpp-tutorial/comments/

## Why it matters
Comments are notes the compiler ignores. Used well, they explain *why* a piece of code exists — context the code itself can't carry. Used badly, they restate *what* the code does and rot the moment the code changes. Learning the distinction early saves years of bad commenting habits.

## Key points
- **Line comment**: `// ...` — runs to end of line.
- **Block comment**: `/* ... */` — spans multiple lines. Do **not** nest them; the first `*/` ends the outermost.
- Use comments to explain **why** (intent, constraints, references), not **what** (the code already says what).
- "Commenting out" code (`// foo();` or wrapping in `/* ... */`) is a common temporary debugging trick.

## Code in this folder
- `main.cpp` — examples of good and bad comment styles side by side.

## Gotchas
- Nested block comments don't work: `/* outer /* inner */ still outer */` — the first `*/` closes it and the rest is a syntax error.
- A comment that contradicts the code is worse than no comment at all. Delete stale comments aggressively.

## Run
    make 1.02
