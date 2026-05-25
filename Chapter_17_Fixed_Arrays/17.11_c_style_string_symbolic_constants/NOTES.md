# 17.11 — C-style string symbolic constants

> learncpp.com: https://www.learncpp.com/cpp-tutorial/c-style-string-symbolic-constants/

## Why it matters
There are three ways to bind a name to a fixed string: `const char name[] = "..."`, `const char* name = "..."`, and (modern) `constexpr std::string_view name = "..."`. They look interchangeable but differ in where the data lives, whether you can pun on the pointer, and what `sizeof` reports. The string-literal `const char*` form is what most older code uses; understanding the trade-offs lets you migrate confidently.

## Key points
- String literals live in a *read-only* segment of the program. Multiple identical literals may share storage (compiler's choice).
- `const char* s = "hello";` — `s` points into that read-only block. Cheap, but `s` could be reassigned to point elsewhere. Mutating `*s` is UB.
- `const char name[] = "hello";` — copies the literal into an array *on the stack* (or in static storage if at namespace scope). The name has array type, can `std::size()` it, can't be repointed.
- `constexpr std::string_view name { "hello" };` — modern best practice. Size known at compile time, no allocation, safe to pass and slice. **Default to this.**
- For program-wide constants prefer `inline constexpr std::string_view kFoo { "..." };` in a header — header-includable, no ODR violation, no static-init order problem.

## Code in this folder
- `main.cpp` — compares the three forms side by side: `sizeof`, decltype, and the `std::string_view` modern alternative.

## Gotchas
- `char s[] = "hello"; s[0] = 'H';` is fine — `s` is a writable copy. `const char* p = "hello"; p[0] = 'H';` is UB.
- `sizeof(charPtr)` is pointer size, *not* string length. `sizeof(charArray)` is length+1.
- Returning `const char*` from a function that points to a local `char[]` dangles. Returning `std::string_view` to a literal is fine — literals have static storage duration.

## Run
    make 17.11
