# 4.1 — Introduction to fundamental data types

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-fundamental-data-types/

## Why it matters
Memory is just bits. Every variable in C++ is a labelled chunk of memory whose **type** tells the compiler how to interpret those bits — same byte pattern, different type = different value. Picking the right fundamental type is the first design decision in every program.

## Key points
- Bit = 0 or 1. Byte = 8 bits (on every platform you'll meet). Memory is byte-addressable; you operate on bytes, not bits.
- A **type** is a label that tells the compiler how to encode/decode a value in memory. Same 32 bits can mean the `int` `1078523331` or the `float` `3.14f`.
- Fundamental categories: **integer** (`short`, `int`, `long`, `long long`), **floating point** (`float`, `double`, `long double`), **boolean** (`bool`), **character** (`char`, `wchar_t`, `char8_t`, `char16_t`, `char32_t`), **null pointer** (`std::nullptr_t`), **void**.
- **Integral** ⊋ **integer**: integral types are the family that store integer values internally — `bool`, the char types, and the standard integers. "Integer types" conventionally means just the standard integers.
- `std::string` is not a fundamental type — it's a standard-library class.

## Code in this folder
- `main.cpp` — declares one variable of each major category and prints it, so you can see the storage representation choice in practice.

## Gotchas
- "Same number of bits" does not mean "same value." A 4-byte `int` and a 4-byte `float` with identical bit patterns are different numbers.
- `char` is *technically* an integral type but prints as a character by default. This bites repeatedly in 4.06, 4.11, 4.12.

## Run
    make 4.01
