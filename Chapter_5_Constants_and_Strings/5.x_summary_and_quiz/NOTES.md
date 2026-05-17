# Chapter 5 — Summary & Quiz

> learncpp.com: https://www.learncpp.com/cpp-tutorial/chapter-5-summary-and-quiz/

## One-page recap

### Constants (5.1, 5.5, 5.6)
- `const T x{ v };` — value can't change after initialization. May be runtime-initialized.
- A **constant expression** is one the compiler can fully evaluate at compile time. Required for array sizes, template args, `case` labels, `static_assert`.
- `constexpr T x{ v };` — like `const`, but the initializer *must* be a constant expression; the compiler enforces it. Prefer `constexpr` over `const` when the value is genuinely compile-time known.
- `const` only promotes integral types to constant-expression status. For non-integral types (`double`, etc.) you need `constexpr`.

### Literals (5.2, 5.3)
- Integer suffixes: `u`, `l`, `ll` (combine: `42ull`). Float suffixes: `f`, `L` (default is `double`).
- `'a'` is a char literal (`int`-valued, type `char`). `"a"` is a 2-char `const char[]` (incl. `'\0'`).
- `'.\n'` is a **multicharacter literal** — implementation-defined, almost always a bug.
- Prefixes: `0` → octal (silent trap), `0x` → hex, `0b` → binary (C++14). Digit separators (`1'000'000`) are cosmetic.
- `std::dec / std::hex / std::oct` are sticky stream manipulators. No `std::bin` — use `std::bitset<N>`.

### As-if rule (5.4)
- Compiler is free to rewrite the program any way it likes as long as observable behavior is preserved.
- Enables constant folding, constant propagation, dead-code elimination. Side effects (I/O, `volatile`) and external calls are barriers.
- `constexpr` is how you *guarantee* compile-time evaluation; otherwise the compiler is allowed to but not required.

### `std::string` (5.7)
- Owning, dynamically sized, value semantics, supports `+`, `==`, `length()`.
- `std::cin >> s` reads one whitespace-delimited token. `std::getline(std::cin, s)` reads a line.
- The `>>` then `getline` mix-up: extract leftover whitespace with `std::cin >> std::ws` before `getline`.
- Pass by `const std::string&`, or better, `std::string_view` for read-only.

### `std::string_view` (5.8, 5.9)
- Non-owning `(ptr, len)`. Cheap to copy, pass *by value*.
- Implicit conversion from `const char*` and `std::string`. Explicit conversion back to `std::string`.
- **Lifetime is your job.** Never outlive the source. Returning a view to a local string is UB. A `std::string` resize invalidates any views into it.
- `remove_prefix(n)` / `remove_suffix(n)` shrink the window without copying.

## Quiz

### Q1 — Why named constants over literal constants?

**Discussion question:** Why are named constants often a better choice than literal constants?

**Answer.** Three reasons, all of them about *humans*, not the compiler:

1. **Names carry meaning.** `gravity` tells the next reader what `9.8` represents and what units it's in. A bare `9.8` doesn't.
2. **One place to change.** If the value needs to update (different planet, different tax rate), you edit the declaration once, not every call site. Search-and-replace on a number is a maintenance bug factory — `9.8` might appear elsewhere for unrelated reasons.
3. **Type and scope come along for free.** `const double gravity{ 9.8 };` is a typed, scoped identifier. The literal `9.8` is just text, and re-typing it invites typos (`9.81` here, `9.8` there).

`constexpr` (5.6) goes further and lets the compiler use the named constant anywhere a constant expression is required — same readability, zero runtime cost.

### Q2 — Find 3 issues in the following code

```cpp
#include <cstdint> // for std::uint8_t
#include <iostream>

int main()
{
  std::cout << "How old are you?\n";

  std::uint8_t age{};
  std::cin >> age;

  std::cout << "Allowed to drive a car in Texas: ";

  if (age >= 16)
      std::cout << "Yes";
  else
      std::cout << "No";

  std::cout << '.\n';

  return 0;
}
```

Expected output:

```
How old are you?
6
Allowed to drive a car in Texas: No

How old are you?
19
Allowed to drive a car in Texas: Yes
```

**Answer.** Three issues:

1. **`std::uint8_t` for `age` is wrong.** `std::uint8_t` is typically a typedef for `unsigned char`, so `std::cin >> age` reads a *single character*, not a number. Typing `19` stores `'1'` (value 49). Use `int` (or `unsigned int` if you really want unsigned), then compare against `16`.
2. **`16` is a magic number.** It's the legal driving age in Texas — give it a name: `constexpr int minDrivingAge{ 16 };`. Future you (or a new state) will thank you.
3. **`'.\n'` is a multicharacter literal.** Two characters inside single quotes is not a string — it's an implementation-defined `int`. Use a string literal `".\n"` (or two separate prints: `'.' << '\n'`).

The fixed program is in `quiz_solutions.cpp` (Q2).

### Q3 — `std::string` vs. `std::string_view`

**Discussion question:** What are the primary differences between `std::string` and `std::string_view`? What can go wrong when using a `std::string_view`?

**Answer.**

`std::string` **owns** its characters. Constructing one allocates (subject to small-string optimization); copying one allocates; it can be resized and modified; it lives as long as the variable does. Use it when you need to hold onto a string — store it in a class, return one from a function, build one up character by character.

`std::string_view` **borrows.** It's a `(pointer, length)` pair — typically 16 bytes — pointing at characters someone else owns. It can't allocate, can't resize, can't modify the underlying characters. Use it for read-only function parameters and for "windows" into existing strings.

The thing that goes wrong is **lifetime.** A `string_view` is just a pointer; nothing keeps the underlying data alive. Classic bugs:

- Returning a `string_view` to a local `std::string` — the local dies at function return.
- Storing `std::string_view{ getString() }` where `getString()` returns by value — the temporary dies at the end of the full expression.
- Taking a view into a `std::string` and then pushing/resizing the string — reallocation invalidates the view (just like iterator invalidation).

Reading through a dangling view is undefined behavior. The fix is always either "make sure the owner outlives the view" or "copy into a `std::string`."

### Q4 — Older of two people

Write a program that asks for the name and age of two people, then prints which person is older.

Sample output:

```
Enter the name of person #1: John Bacon
Enter the age of John Bacon: 37
Enter the name of person #2: David Jenkins
Enter the age of David Jenkins: 44
David Jenkins (age 44) is older than John Bacon (age 37).
```

**Hint.** Input the person's name using `std::getline()` so names with spaces work.

Worked solution lives in `quiz_solutions.cpp` (Q4). Notes on design:

- Names are read with `std::getline`, because `"John Bacon"` has a space.
- The age extraction (`std::cin >> age1`) leaves a newline in the buffer. The next `std::getline` would consume it and read an empty line. Discard with `std::cin >> std::ws` before the next `getline`.
- The "is older" message is built by picking the older/younger pair with a couple of locals — keeps the print statement linear and avoids duplicating the format string.

### Q5 — Why can't `age1` in main be `constexpr`?

**Discussion question:** In the solution to Q4, why can't variable `age1` in `main` be `constexpr`?

**Answer.** `age1` is initialized from `std::cin` — its value isn't known until the user types it, which is at runtime. `constexpr` requires the initializer to be a *constant expression* (5.5), i.e. fully evaluable by the compiler. Reading from a stream is the textbook example of something that isn't.

`const int age1{ ... };` would be legal — `age1` won't change after it's set — but `constexpr int age1{ ... };` is a compile error. This is exactly the distinction lesson 5.5 builds toward: `const` constrains *change*, `constexpr` constrains *when the value is known*.

## Run

    make 5.x

`quiz_solutions.cpp` has worked code for Q2 (the fixed driving-age program) and Q4 (older-of-two-people), with inline commentary.
