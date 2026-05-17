# Chapter 6 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-6-summary-and-quiz/

## One-page recap

### Precedence and associativity (6.1)
- **Precedence** picks which operator binds first (`*` before `+`).
- **Associativity** breaks ties (subtraction is left-to-right, assignment is right-to-left).
- **Order of evaluation of operands** is *not* governed by precedence — for most operators it's unspecified. Parenthesize for the reader; never rely on operand-evaluation order.

### Arithmetic (6.2)
- `+ - * / %` plus unary `+/-`. Compound `+= -= *= /= %=`.
- Integer division truncates toward zero. Cast one operand to `double` for fractional results.
- Integer `/0` is UB. Float `/0.0` is `inf` / `nan` on IEEE 754.

### Remainder & exponentiation (6.3)
- `%` is integer-only; sign follows the dividend. Test odd as `x % 2 != 0`, not `== 1`.
- No `^` exponent operator (that's XOR). `std::pow` is `double`-precision — write your own `intPow` for exact integer answers.

### Increment/decrement & side effects (6.4)
- Prefix `++x` returns the new value; postfix `x++` returns the old. Prefer prefix.
- Never use a variable that has a side effect more than once in a single statement — undefined behavior.

### Comma operator (6.5)
- Evaluates left, then right, yields right. **Lowest precedence in C++** — `z = a, b;` is `(z = a), b;`. Idiomatic only inside `for` headers.

### Conditional operator (6.6)
- `c ? a : b` — only one arm evaluated; arms must share a type.
- Use for: `const` init, in-line stream pluralization, single-line returns. Past one level of nesting, switch to `if`/`else if`.

### Relational & float comparisons (6.7)
- Six comparisons return `bool`. Avoid `b == true`; just write `b`.
- `==`/`!=` on computed floats is almost always wrong. Use a hybrid absolute+relative `approxEqual`. `nan != nan` always.

### Logical operators (6.8)
- `! && ||`. `&&` and `||` **short-circuit** — useful as null guards, dangerous if RHS has needed side effects.
- Mixed `&&`/`||` — parenthesize anyway. De Morgan: `!(a && b) == !a || !b`.

## Quiz

### Q1 — Pluralizing apples

Write a program with two functions:

**`std::string_view getQuantityPhrase(int quantity)`** — returns a descriptor:

| Quantity   | Phrase         |
|------------|----------------|
| `< 0`      | `"negative"`   |
| `0`        | `"no"`         |
| `1`        | `"a single"`   |
| `2`        | `"a couple of"`|
| `3`        | `"a few"`      |
| `> 3`      | `"many"`       |

**`std::string_view getApplesPluralized(int quantity)`** — returns `"apple"` if quantity is `1`, otherwise `"apples"`. **Must use the conditional operator.**

`main()` should produce:

```
Mary has a few apples.
How many apples do you have? 1
You have a single apple.
```

(The `1` on the second line is read from `std::cin`. In the worked solution we hard-code it so the program is non-interactive and reproducible.)

Hints:
- Return type is `std::string_view`, not `std::string` — these functions only return string literals, so there's nothing to own.
- `getQuantityPhrase` is just a chain of `if` / `else if` / `else`. Don't try to cram it into one big ternary — the spec only mandates the conditional operator in `getApplesPluralized`.

## Run

    make 6.x

`quiz_solutions.cpp` has the worked solution with inline notes on the type choice and the ternary placement.
