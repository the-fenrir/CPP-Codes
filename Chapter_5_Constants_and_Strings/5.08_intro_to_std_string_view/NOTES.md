# 5.8 — Introduction to `std::string_view`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-stdstring_view/

## Why it matters
`std::string` is great, but copying one is not free. A function that just wants to *read* characters — `print`, `length`, `starts_with` — shouldn't force the caller to either own a `std::string` or pay for one. `std::string_view` is a *non-owning view*: a `(pointer, length)` pair that binds cheaply to a string literal, a `std::string`, a `char[]`, or another view. It's the right type for read-only string parameters.

## Key points
- `#include <string_view>`. The type is `std::string_view`.
- Implicit conversion from `const char*`, `const char[]`, and `std::string` (the last via `std::string`'s `operator string_view`). The reverse — `string_view` → `std::string` — is *explicit*.
- A view is small (typically 16 bytes on 64-bit: pointer + length) and trivially copyable. Pass by value, not by reference.
- All the read-only `std::string` methods are there: `length()`, `size()`, `front()`, `back()`, `substr()`, `find()`, comparison operators.
- A view does **not** own its data. If the underlying string disappears, the view dangles. Covered in detail in 5.9; for now, the rule is "never store a view longer than the thing it points at."
- **Function parameters.** Default to `std::string_view` for read-only access: `void print(std::string_view s);`. Accepts literals and `std::string`s without copying.

## Code in this folder
- `main.cpp` — bind a `string_view` to a literal and to a `std::string`, pass to a function, use `substr`, and show the cheap copy.

## Gotchas
- `std::string_view` is *not* guaranteed to be null-terminated. `view.data()` may point at characters past the view's length. Don't pass `view.data()` to `printf` or C APIs unless you've ensured null-termination (e.g., constructed from a string literal or from a `std::string`'s full range).
- A literal `"hi"` is `const char[3]` — converting it to `string_view` is free and lifetime-safe (the literal lives forever).
- Implicit `std::string → std::string_view` is convenient but dangerous in returning contexts. `std::string_view bad(){ std::string s{"x"}; return s; }` returns a view to a destroyed string.

## Run
    make 5.08
