# Chapter 1 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-1-summary-and-quiz/

## One-page recap

### Program structure (1.1)
- A C++ program is a list of **statements**, grouped into **functions**. Most statements end with `;`.
- Every executable program needs exactly one function named `main` returning `int`.
- `#include <iostream>` is a preprocessor directive (no `;`), not a statement.

### Comments (1.2)
- `// line` and `/* block */`. Don't nest block comments.
- Explain *why*, not *what*. Delete stale comments.

### Objects and variables (1.3)
- An **object** (memory sense) is a typed region of memory; a **variable** is a named object.
- `int x;` defines `x` but does **not** give it a value.

### Initialization vs. assignment (1.4)
- **Initialization** happens once, at creation; **assignment** can happen many times after.
- C++ has multiple init forms; prefer **brace-init** (`int x{ 5 };` or `int x{};`).
- Brace-init rejects narrowing conversions — that's a feature.

### iostream (1.5)
- `std::cout << ...;` for output, `std::cin >> ...;` for input, chain freely.
- Use `'\n'` over `std::endl` (the latter flushes the buffer, usually wastefully).

### Uninitialized variables & UB (1.6)
- Reading an uninitialized built-in is **undefined behavior**.
- UB is not "you get garbage" — it's "anything is permitted, including silently passing tests today and failing tomorrow."
- Always initialize. `int x{};` if you don't have a real value yet.

### Keywords & identifiers (1.7)
- Identifiers: letters, digits, `_`; can't start with a digit; can't be a keyword; case-sensitive.
- Avoid leading underscores (reserved) and meaningless names. Names are documentation.

### Whitespace and formatting (1.8)
- The compiler ignores whitespace; readers don't.
- One statement per line, consistent indent, always brace `if`/`for`/`while` bodies.

### Literals and operators (1.9)
- **Literal** = value baked into source (`5`, `3.14`, `'A'`, `"hi"`, `true`).
- Operators: unary (`-x`), binary (`a + b`), ternary (`c ? a : b`). Precedence + associativity decide grouping — use brackets when in doubt.
- `=` is assignment, `==` is comparison — never confuse them.

### Expressions (1.10)
- Anything that evaluates to a value is an expression.
- An expression followed by `;` is an expression statement — that's how an expression has an effect.

### First program (1.11)
- Write a little, compile, run; repeat. The compile-run loop after every meaningful change is the most important habit in C++.

---

## Quiz

### Q1 — What's the difference between initialization and assignment? How many times can each happen?

**Discussion question.** Answer in your own words before reading the worked answer in `quiz_solutions.cpp`'s top comment.

### Q2 — When does undefined behavior occur, and what are its consequences?

**Discussion question.** Same format — answer first, then check.

### Q3 — Sum and difference of two integers

Write a program that asks the user for two integers and prints both their sum and their difference. To stay within the repo's non-interactive build, the worked solution uses two hard-coded values (`a = 6`, `b = 4`) and adds the interactive `std::cin` version in comments.

**Expected output** for `a = 6`, `b = 4`:

```
Enter an integer: 6
Enter another integer: 4
6 + 4 is 10.
6 - 4 is 2.
```

*Hint from learncpp:* use `".\n"` (a string literal) when you want to print "period then newline" as two characters. A character literal can hold exactly one character, so `'.\n'` would be wrong.

## Run

    make 1.x

`quiz_solutions.cpp` has the worked code for Q3 plus written-out answers to Q1 and Q2 in its header comment.
