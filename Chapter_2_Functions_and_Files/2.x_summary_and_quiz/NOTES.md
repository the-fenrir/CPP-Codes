# Chapter 2 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-2-summary-and-quiz/

## One-page recap

### Functions (2.1–2.6)
- A function is a named, reusable sequence of statements. Call with `name()`.
- **Return type** declared before the name. `void` = no value returned. `main()` returns `int`; `0` = success.
- **Parameters** are locals initialized from the **arguments** at the call site. C++ defaults to **pass by value** — the function gets a copy.
- Locals' **scope** ends at the enclosing `}`; their **lifetime** ends with it too. Each call creates fresh locals.
- Extract a function when: code repeats, has a clear single responsibility, or the call site would read more clearly with a name.

### Forward declarations and multi-file programs (2.7–2.8)
- A **forward declaration** (a.k.a. **function prototype**) declares a name without defining it: `int add(int, int);`.
- **One Definition Rule (ODR)**: many declarations, exactly one definition program-wide.
- Each `.cpp` is a separate **translation unit (TU)**. The linker resolves cross-TU calls.
- To call code from another `.cpp`, declare it in this one (directly or via a header) and pass both `.cpp`s to the build.

### Namespaces (2.9)
- A **namespace** is a named scope. Same name in different namespaces = different entities.
- The standard library lives in `std::`. Prefer `std::cout` to `using namespace std;`, especially in headers.
- Use `::` (scope resolution) to qualify.

### Preprocessor (2.10)
- Runs *before* the compiler. Does text substitution: `#include`, `#define`, `#ifdef`.
- `#include <foo>` (system) vs. `#include "foo"` (user). Both are literal paste.
- Macros are unscoped and untyped — prefer `constexpr` for constants and `inline` functions over function-like macros.

### Header files and header guards (2.11–2.12)
- A **header** centralizes declarations so callers don't each maintain their own prototypes. Implementation lives in the matching `.cpp`.
- Headers must be **self-contained** and **idempotent** — wrap every header with a header guard (`#pragma once` or `#ifndef X / #define X / #endif`).
- Guards prevent *multiple inclusion in the same TU*. They do *not* fix ODR violations across TUs. So: never define non-inline non-template functions or non-inline variables at file scope in a header.

### Designing programs (2.13)
- Goal → requirements → tools → decompose into functions → implement → test → iterate.
- Stub functions out before fleshing them in. Get end-to-end running first, then improve.
- A function name that needs "and" probably wants to be two functions.

## Quiz

The three quiz problems progressively refactor the same program. Treat them as one project.

### Q1 — Single-file version

Write a single-file program (named `main.cpp`) that:

1. Reads two integers from the user.
2. Adds them.
3. Prints the result.

Structure it with three functions:

- `int readNumber()` — prompts the user, reads one integer from `std::cin`, returns it.
- `void writeAnswer(int x)` — prints `The answer is: <x>`.
- `int main()` — calls `readNumber()` twice, sums the results, calls `writeAnswer()`.

Expected interaction (input shown in `<...>`):

```
Enter an integer: <3>
Enter an integer: <4>
The answer is: 7
```

### Q2 — Split across two files using forward declarations

Refactor Q1 into two files:

- `io.cpp` — contains the definitions of `readNumber()` and `writeAnswer()`. No `main()`.
- `main.cpp` — contains `main()`. It does **not** include any header for `readNumber`/`writeAnswer`; instead, it forward-declares them at the top.

Behavior must be identical to Q1.

### Q3 — Replace the forward declarations with a header file

Refactor Q2 again:

- Add `io.h` containing the declarations of `readNumber()` and `writeAnswer()`, wrapped in a header guard.
- `io.cpp` `#include`s `io.h` and defines the functions.
- `main.cpp` `#include`s `io.h` instead of writing its own forward declarations.

Behavior must be identical to Q1.

## Run

    make 2.x

`quiz_solutions.cpp` is a single self-contained worked solution showing all three layers. It uses one TU rather than splitting into three files because:

- Q1 is trivially a single TU.
- Q2 and Q3's value is *structural*, not behavioral — the runtime output is identical. Lesson 2.08 and 2.11 in this chapter already demonstrate the actual multi-file layout. The quiz solution focuses on the design commentary; comments at the top of the file describe what Q2's `io.cpp` / `io.h` split would look like and why Q3's header-file version is the better long-term shape.

The `cin` reads at runtime are wrapped in a small helper that falls back to hardcoded inputs when stdin is not a terminal, so `make 2.x` runs non-interactively (important: the build target needs to terminate without a human typing).
