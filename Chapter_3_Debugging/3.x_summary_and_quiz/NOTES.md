# Chapter 3 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-3-summary-and-quiz/

## One-page recap

### Two kinds of errors (3.1)
- **Syntax error** — grammar violation. Compiler catches it. Fix the *first* one reported, then recompile.
- **Semantic error** — legal code, wrong meaning. Compiler can't catch (warnings catch *some*). Only tests or a debugger find them.

### The process (3.2, 3.3)
Five steps: **find root cause → understand → choose a fix → repair → retest**. Step 1 is 90% of the work. To find the root cause: **reproduce reliably, then binary-search the execution** by checking program state at progressively narrower points. One change at a time.

### Ad-hoc tactics (3.4, 3.5)
- **Comment out half** the code, narrow until the bug appears/disappears.
- **Print values** at decision points — loop bounds, branches, function entry/exit. Tag prints (`[DBG]`), keep them on `std::cerr` (unbuffered, redirectable via `2>`).
- Promote one-off prints to **`#ifdef ENABLE_DEBUG`** macros so they cost zero in release and can't accidentally ship live.

### The debugger (3.6–3.9)
Built-in to every IDE; from a terminal use **`lldb`** (macOS) or **`gdb`** (Linux) on a `-g` binary.

| Verb            | What it does                                               | lldb / gdb         |
|-----------------|------------------------------------------------------------|--------------------|
| Step into       | Enter the next call                                        | `s` / `step`       |
| Step over       | Run next stmt to completion without entering               | `n` / `next`       |
| Step out        | Run until current function returns                         | `finish`           |
| Breakpoint      | Pause when execution hits this line                        | `b file:line`      |
| Conditional     | Break only when an expression is true                      | `b ... if cond` (gdb) / `breakpoint set -c` (lldb) |
| Continue        | Resume until next break                                    | `c`                |
| Watch a value   | Show this expression at every pause                        | `display expr`     |
| Watchpoint      | Pause when a variable's value *changes*                    | `watch x`          |
| Call stack      | Show the chain `main → ... → here`                         | `bt`               |
| Switch frame    | Inspect a caller's locals without leaving the pause        | `up`, `down`, `f N` |

Use breakpoints to *get to* the bug, stepping to *narrow it down*, watches to *see state* change, and the call stack to find *who* caused the bad input.

### Shifting left (3.10)
The cheapest bug is the one you never wrote.
- **Compile with warnings on** (`-Wall -Wextra -Wpedantic`) and fix every one.
- **Static analyzers** (`clang-tidy`, `cppcheck`) catch what the compiler doesn't.
- **Sanitizers** (`-fsanitize=address,undefined`) find UB at runtime with file:line.
- **`static_assert`** / **`assert`** / **defensive validation** + **unit tests** — pick whichever runs *earliest*: compile-time > debug-build > test-run > production.

## Quiz

### Q1 — Sum doesn't add up

This program is supposed to read two numbers and print their sum, but it prints the wrong answer. Identify the bug and fix it.

```cpp
#include <iostream>

int readNumber(int x)
{
    std::cout << "Please enter a number: ";
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum is: " << x << '\n';
}

int main()
{
    int x {};
    readNumber(x);
    x = x + readNumber(x);
    writeAnswer(x);

    return 0;
}
```

**Hint.** `readNumber` takes `x` *by value* and returns a number. What does the first `readNumber(x);` line actually *do* with the return value? And on the second line, what value of `x` are we passing in — and does it matter?

### Q2 — Division by zero

This program reads two numbers and prints their quotient. On inputs `8` and `4` it crashes with a division by zero. Identify the bug.

```cpp
#include <iostream>

int readNumber()
{
    std::cout << "Please enter a number: ";
    int x {};
    std::cin >> x;
    return x;
}

void writeAnswer(int x)
{
    std::cout << "The quotient is: " << x << '\n';
}

int main()
{
    int x{ };
    int y{ };
    x = readNumber();
    x = readNumber();
    writeAnswer(x/y);

    return 0;
}
```

**Hint.** Look very carefully at the two assignments before `writeAnswer`. What variable is on the left of each? And given that, what is `y` when the division runs?

### Q3 — Read the call stack

For the program below, what does the call stack look like at the marked point (`// here`)? List frames innermost-first, the way `lldb`/`gdb` show them with `bt`.

```cpp
#include <iostream>

void d()
{ // here
}

void c()
{
}

void b()
{
    c();
    d();
}

void a()
{
    b();
}

int main()
{
    a();

    return 0;
}
```

**Answer.** At the marked point execution is inside `d`, which was called from `b`, which was called from `a`, which was called from `main`. So the stack is:

```
frame 0: d()        ← currently executing
frame 1: b()
frame 2: a()
frame 3: main()
```

Note that `c()` is **not** on the stack — `b` called `c` and `c` returned before `b` called `d`. The stack records *unfinished* calls, not history.

### Q4 (extra credit) — Wrong sum, char edition

This program is supposed to read two integers and print their sum. On inputs `2` and `3`, it prints `101` instead of `5`. Identify the bug.

```cpp
#include <iostream>

int readNumber()
{
    std::cout << "Please enter a number: ";
    char x{};
    std::cin >> x;

    return x;
}

void writeAnswer(int x)
{
    std::cout << "The sum is: " << x << '\n';
}

int main()
{
    int x { readNumber() };
    int y { readNumber() };
    writeAnswer(x + y);

    return 0;
}
```

**Hint.** What does `std::cin >> x` actually read when `x` is a `char`? When that `char` is then returned and stored in an `int`, what numeric value ends up in there for the input `'2'`?

## Run

    make 3.x

`quiz_solutions.cpp` has the fixed code for Q1, Q2, and Q4, with the buggy original next to the fix and a comment explaining the root cause. Q3 is purely a discussion question — the answer is above.
