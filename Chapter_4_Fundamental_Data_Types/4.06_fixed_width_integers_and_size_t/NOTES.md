# 4.6 — Fixed-width integers and `size_t`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/fixed-width-integers-and-size-t/

## Why it matters
The standard's "minimum size" promise for `int` etc. is fine for casual use but useless when you need a specific width — wire protocols, binary file formats, bit manipulation. C++11 added `<cstdint>` with types whose sizes are *guaranteed*. Plus a special unsigned type, `std::size_t`, that the standard library uses everywhere for sizes and indices.

## Key points
- `<cstdint>` provides `std::int8_t`, `std::int16_t`, `std::int32_t`, `std::int64_t` and unsigned counterparts `std::uint8_t` … `std::uint64_t`. Exact widths, two's-complement signed.
- "Fast" and "least" variants exist (`std::int_fast32_t`, `std::int_least16_t`). They trade strict width for "at least this many bits, optimized for speed / minimal storage." Their actual size is implementation-defined.
- **8-bit quirk**: `std::int8_t` and `std::uint8_t` are typically typedefs for `signed char` / `unsigned char`. They **print as characters**, not numbers. Cast to `int` for numeric output, and they won't read numbers from `std::cin` directly either.
- `std::size_t` (from `<cstddef>`) is the standard library's unsigned size/index type. It's the return type of `sizeof`, of `.size()` on standard containers, of `strlen`. Its width matches the platform's address width (32 or 64 bits).

## Code in this folder
- `main.cpp` — prints sizes of every `<cstdint>` type, demonstrates the `std::uint8_t` "prints as character" gotcha, and uses `std::size_t` as a `sizeof` result.

## Gotchas
- `std::int8_t x{ 65 }; std::cout << x;` prints `A`, not `65`. Always wrap small fixed-width prints in `static_cast<int>(x)`.
- `size_t` being unsigned brings back every signed/unsigned comparison hazard from 4.5. Mixing `size_t` with a signed `int` index is a top source of compiler warnings.

## Run
    make 4.06
