# 4.5 — Unsigned integers, and why to avoid them

> learncpp.com: https://www.learncpp.com/cpp-tutorial/unsigned-integers-and-why-to-avoid-them/

## Why it matters
Unsigned types look harmless — "I only want non-negative values, so why not gain a bit of range?" — but they introduce two failure modes (modular wrap-around and silent signed→unsigned conversion in mixed expressions) that produce gigantic positive numbers where you expected `-1`. Most modern C++ guidance is: don't use unsigned for *quantities*.

## Key points
- Unsigned arithmetic is **modular** (well-defined) — assigning out-of-range values wraps. `unsigned char x{ 280 }` stores `24` (280 mod 256). `unsigned x{ -1 }` stores the type's maximum.
- That well-definedness is a trap: the wrap is silent. A loop like `for (unsigned i{ n }; i >= 0; --i)` is infinite because `i` cannot become negative.
- **Signed/unsigned mixing**: in expressions combining a signed and an unsigned value of the same rank, the signed operand is converted to unsigned. So `-1 < 1u` is `false` — `-1` becomes the unsigned max, which is huge.
- Best practice (Google, Bjarne, Herb): **use signed integers for quantities**; reserve unsigned for bit manipulation, intentional wrap, and unavoidable interop (`size_t` indexing).

## Code in this folder
- `main.cpp` — three concrete bugs: unsigned underflow, signed/unsigned comparison going wrong, and `-1` passed to an unsigned parameter.

## Gotchas
- `std::size_t` (covered in 4.6) is unsigned. `for (std::size_t i = 0; i < v.size(); ++i)` is fine — `i` only goes up. But `for (std::size_t i = v.size() - 1; i >= 0; --i)` is the classic infinite loop.
- Compilers can warn about signed/unsigned mismatch (`-Wsign-compare`) — heed the warning, don't silence it with a cast.

## Run
    make 4.05
