# 9.6 — `assert` and `static_assert`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/assert-and-static_assert/

## Why it matters
`assert` and `static_assert` are how you write *executable comments*: "this expression must be true, and if it isn't, I want to know loudly." They're the cheapest line of defense against bugs. The trick is knowing what they're for — and what they're *not* for.

## Key points
**`assert(expr)`** (`<cassert>`)
- Macro. Evaluates `expr` at *runtime*. If false, prints file:line and aborts.
- **Compiled out when `NDEBUG` is defined** — release builds typically `-DNDEBUG`, so asserts vanish. Don't put side effects inside (`assert(--n > 0)` is a bug).
- Purpose: catch **bugs** — situations the programmer believes are impossible.

**`static_assert(expr, msg)`**
- Keyword, not a macro. Evaluated at *compile time*. Failure is a compile error.
- `expr` must be a constant expression. Works on `sizeof`, type traits, template parameters, `constexpr` values.
- Always on — no `NDEBUG`. Free at runtime.

**Asserts ≠ error handling:**
- `assert` is for *impossible* situations (broken invariants, bugs).
- `if (...) handle()` is for *possible* situations (bad input, missing file).
- Test: "could a well-formed user / well-written caller trigger this?" — if yes, it's not an assertion case.

**Idiomatic uses of `assert`:**
- Precondition checks at the top of internal functions.
- Postcondition checks on a function's result before returning.
- "Can't happen" branches: `assert(false && "unreachable");`.
- Sanity checks after a long computation: `assert(invariant_holds());`.

**Idiomatic uses of `static_assert`:**
- Lock down a `sizeof` or alignment: `static_assert(sizeof(int) >= 4);`.
- Constrain templates: `static_assert(std::is_integral_v<T>);`.
- Validate compile-time computation: `static_assert(factorial(5) == 120);`.

## Code in this folder
- `main.cpp` — three `static_assert` checks (all pass at compile time) and three `assert` checks (all hold at runtime). The "failing" cases are written inside `if (false) { ... }` blocks with a comment showing what would fire if enabled, so the program runs to completion.

## Gotchas
- **No side effects in `assert`.** `assert(buf.read() != EOF)` is a bug — in release builds the read never happens.
- **`assert(false && "message")`** is the idiom for unreachable code; the `&&` forces the message into the abort output.
- **`static_assert(expr);`** (no message) works since C++17 but a message makes the diagnostic vastly more useful.
- **Don't use `assert` to validate user input.** A program that aborts on a typo is worse than one that re-prompts.

## Run
    make 9.06
