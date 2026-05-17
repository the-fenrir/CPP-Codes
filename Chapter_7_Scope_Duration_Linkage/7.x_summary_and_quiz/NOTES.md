# Chapter 7 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-7-summary-and-quiz/

## One-page recap

### The three orthogonal properties (7.1, 7.3, 7.4, 7.12)
- **Scope** — where the *name* is visible: block / namespace / class.
- **Duration** — how long the *storage* lives: automatic / static / dynamic / thread.
- **Linkage** — whether the same name in different TUs refers to the same entity: none / internal / external.
- These are independent. Every declaration has all three.

### Blocks & namespaces (7.1, 7.2, 7.13, 7.14)
- `{ }` opens a new block scope. Always use a block for a non-trivial `if`/`for` body.
- `namespace Foo { ... }` partitions the global namespace. Can be reopened anywhere.
- `using` **declaration** (one name) is fine, even at file scope. `using` **directive** (whole namespace) is fine inside a function; dangerous at file scope; never in a header.
- **Unnamed namespace** is the modern replacement for file-scope `static`. **Inline namespace** is for library versioning.

### Locals (7.3, 7.11)
- Default: block scope, automatic duration, no linkage. Brace-init or you get garbage.
- `static` local: block scope, **static** duration, no linkage. Persists between calls; initialized once.
- Returning a pointer/reference to a non-static local dangles.

### Globals (7.4, 7.6, 7.7, 7.8)
- Non-const file-scope variable: external linkage. **Avoid.** They couple unrelated functions invisibly.
- `const`/`constexpr` at file scope: internal linkage by default — each TU gets its own copy.
- To *share* a global across files: `extern int g_x;` in a header, `int g_x{};` in one `.cpp`. Modern preference for *constants* is `inline constexpr` in a header.
- Globals are zero-initialized by default (locals are not).

### `inline` & sharing constants (7.9, 7.10)
- Modern meaning of `inline`: "this entity may have one definition per TU; the linker treats them as one." Nothing to do with optimizer inlining.
- `inline constexpr T g_x{};` in a header is the canonical way to share named compile-time constants across files. Use a `namespace Constants { ... }` for tidiness.

### Decision table you should be able to fill in
| Need | Form |
|---|---|
| Helper used only in this `.cpp` | unnamed namespace (preferred) or `static` |
| Constants shared across `.cpp`s | `inline constexpr` in a header |
| Function-private counter | `static` local |
| Truly shared mutable state | usually a class with one owner; if it must be global, accept the hazards |

## Quiz

### Q1 — Fix the dangling-statement bug
The chapter quiz gives this program:

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a positive number: ";
    int num{};
    std::cin >> num;

    if (num < 0)
        std::cout << "Negative number entered.  Making positive.\n";
        num = -num;

    std::cout << "You entered: " << num;
    return 0;
}
```

Only the first statement after `if (num < 0)` is the `if` body. `num = -num;` runs unconditionally, so a positive input is flipped negative. Fix: wrap both lines in a block.

### Q2 — `constants.h` for `Constants::maxClassSize`
Write a header that makes the caller below run. Use `inline constexpr`; the value is `35`.

```cpp
#include "constants.h"
#include <iostream>

int main()
{
    std::cout << "How many students are in your class? ";
    int students{};
    std::cin >> students;

    if (students > Constants::maxClassSize)
        std::cout << "There are too many students in this class";
    else
        std::cout << "This class isn't too large";
    return 0;
}
```

The recipe is exactly 7.10's: `namespace Constants { inline constexpr int maxClassSize{ 35 }; }`. `inline` makes it sharable; `constexpr` makes it compile-time; the namespace keeps the name tidy.

### Q3 — `int accumulate(int x)`
Write `accumulate` so it returns the running sum of all `x` passed across all calls:

```
accumulate(4) → 4
accumulate(3) → 7
accumulate(2) → 9
accumulate(1) → 10
```

The whole point of the exercise is to use a **static local** to keep the running total across calls — see 7.11. Quiz solution does exactly that.

### Q3b (extra credit) — two shortcomings of `accumulate()`

**Answer.**

1. **Untestable / hidden state.** The function's output depends on call history, not just on the current argument. There's no way to "reset" it for a unit test except by restarting the process, and tests that run in any order interfere with each other. The function's signature (`int accumulate(int)`) lies about its purity.
2. **Not reusable for multiple independent sums.** You can keep exactly one running total per program. The moment two callers want their own sums (e.g. summing two different streams), you're stuck — the state is bound to the function, not to the caller. A class with an instance per sum, or a free function that takes the running total as a parameter, is more flexible.

(Bonus: it's not thread-safe in a useful way. C++11 makes the *initialization* of static locals thread-safe, but the `++`/`+=` afterward is not — concurrent callers would race.)

## Run

    make 7.x

`quiz_solutions.cpp` has worked code for Q1, Q2, and Q3, plus inline design commentary.
