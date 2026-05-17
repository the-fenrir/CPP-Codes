# 13.1 — Introduction to program-defined (user-defined) types

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-program-defined-user-defined-types/

## Why it matters
Built-in types (`int`, `double`, `bool`, `char`, ...) bottom out fast. Real programs need *named* types that carry meaning: a "Color", a "Monster", a "Fraction". C++ lets you define your own — and once you do, the type system can enforce things it couldn't before (you can't accidentally pass a `Color` where the function wanted a `Direction`). The rest of this chapter and all of Chapters 14–15 are different ways of defining program-defined types.

## Key points
- **Built-in types** are baked into the language. **Program-defined types** (a.k.a. user-defined types) are the ones *you* declare: `enum`, `enum class`, `struct`, `class`, `union`.
- A program-defined type must be **defined** before it's used in that translation unit — typically via a header included where needed. Multiple TUs may each see the definition; the **one-definition rule** allows identical type definitions in different TUs.
- Naming convention: program-defined type names start with a capital letter and have no suffix (`Fraction`, not `fraction_t`).
- A type definition does **not** allocate storage — only declarations of *variables of that type* do.

## Code in this folder
- `main.cpp` — declares a tiny `enum` and a tiny `struct` to make "this is what we'll spend the chapter doing" concrete.

## Gotchas
- The header that defines a program-defined type can be included in many TUs; the type definition itself doesn't violate ODR because identical definitions are allowed for types (unlike for non-inline functions/variables).
- Forgetting the trailing semicolon after a `struct`/`class`/`enum` definition is the #1 beginner compile error in this chapter.

## Run
    make 13.01
