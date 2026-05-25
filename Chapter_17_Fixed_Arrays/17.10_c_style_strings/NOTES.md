# 17.10 — C-style strings

> learncpp.com: https://www.learncpp.com/cpp-tutorial/c-style-strings/

## Why it matters
A C-style string is just a `char` array terminated by a `\0` null byte — no separate length, no class, no bounds checking. Every string literal in C++ is one (`"hello"` has type `const char[6]`, including the terminator). Most of the time you should turn it into a `std::string` or `std::string_view` immediately. But you need to know what's happening because the entire C standard library and most OS APIs still speak this dialect.

## Key points
- Literal: `"hello"` → `const char[6]` (5 chars + `\0`). `sizeof("hello")` is 6.
- Declaration: `char name[] { "Alex" };` — size deduced to 5, terminator included. `char name[10] { "Alex" };` — pads remaining slots with `\0`.
- Useful `<cstring>` functions: `std::strlen` (length, *not* counting `\0`), `std::strcpy` (UNSAFE, no bounds), `std::strncpy` (still tricky), `std::strcmp` (compares lexicographically, returns 0 on equal).
- Reading with `std::cin >> buf;` is a classic buffer-overflow vector. Use `std::cin.getline(buf, size);` — caps the read at `size - 1`, always writes the terminator.
- `std::cout` prints a `const char*` as a string (printing until `\0`). Printing a `char*` that *doesn't* point to a null-terminated buffer is UB.
- Prefer `std::string` / `std::string_view` everywhere except when calling a C API that demands `const char*`. `std::string::c_str()` is your bridge.

## Code in this folder
- `main.cpp` — declare a C string, check `strlen` vs. `sizeof`, copy with `strncpy` and manually null-terminate, compare with `strcmp`.

## Gotchas
- `strlen` walks until `\0` — O(n), and UB if there's no terminator. `sizeof` is O(1) compile-time, includes the terminator.
- `strcpy` doesn't bound. One careless call and you've corrupted the stack. Modern compilers warn but the warning isn't always loud.
- `char* s = "hello";` is deprecated and ill-formed since C++11 — string literals are `const char[]`. Always `const char*`.

## Run
    make 17.10
