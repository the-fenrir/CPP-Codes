# 1.6 — Uninitialized variables and undefined behavior

> learncpp.com: https://www.learncpp.com/cpp-tutorial/uninitialized-variables-and-undefined-behavior/

## Why it matters
Reading a variable that was never initialized is **undefined behavior** (UB). UB is not "you get garbage" — it's "the standard places no requirement on what happens." The compiler is allowed to delete the surrounding code, return different values on each call, or do something stranger. This is the single largest source of "but it worked on my machine" bugs in C and C++.

## Key points
- A built-in type variable defined without an initializer (`int x;`) holds an **indeterminate value**. Reading it = UB.
- UB symptoms are unstable: works in debug, fails in release; works today, fails tomorrow.
- Rule: **always initialize variables when you define them.** `int x{};` if you have no better value yet.
- Modern compilers warn (`-Wuninitialized` / `-Wall`) when they can prove a read of an uninitialized value — but they can't always prove it.

## Code in this folder
- `main.cpp` — initializes everything (safe). A commented-out block shows the UB pattern you must avoid.

## Gotchas
- Some types (e.g. `std::string`, `std::vector`) have default constructors that initialize them for you. The trap is only built-ins (`int`, `double`, `char`, pointers, ...).
- Static and global variables *are* zero-initialized by the language. Local built-ins are not. Don't rely on the global rule to bail you out.

## Run
    make 1.06
