# 5.2 — Literals

> learncpp.com: https://www.learncpp.com/cpp-tutorial/literals/

## Why it matters
Every value baked directly into source code is a *literal*. The compiler has to give each one a type, and that type comes from the literal's spelling — `5` is `int`, `5.0` is `double`, `5.0f` is `float`, `"5"` is `const char[2]`. Get the suffix wrong and you silently change the type of the expression, which silently changes overload resolution and arithmetic.

## Key points
- **Integer literals**: `42` is `int`. Add `u`/`U` for unsigned, `l`/`L` for long, `ll`/`LL` for long long. Combine: `42ull`.
- **Floating-point literals**: `3.14` is `double` (the default). Use `3.14f` for `float`, `3.14L` for `long double`. Scientific form: `1.5e3` = 1500.0.
- **Character literals**: `'a'` is `int` in C, but `char` in C++. `'\n'` is one char (newline). Multi-character literals like `'.\n'` are *implementation-defined* — almost always a bug; the compiler usually warns.
- **String literals**: `"hello"` has type `const char[6]` (5 chars + `\0`). They live in static storage; their address is valid for the whole program.
- **Boolean literals**: `true` and `false`, type `bool`.
- C++14 introduces digit separators: `1'000'000` for readability. Doesn't change the value.
- Prefer named constants (5.1) over inline literals — a literal is fine for genuinely-self-evident values (`0`, `1`, `'\n'`), not for "magic numbers" with domain meaning.

## Code in this folder
- `main.cpp` — literal types via suffixes, the multichar-literal trap, digit separators, and a string literal's underlying array type.

## Gotchas
- `'.\n'` is a *multicharacter literal*, not a string. It has type `int`, value implementation-defined. Use `".\n"` (string literal) or two prints.
- `5 / 2` is `2` (int division). `5.0 / 2` is `2.5`. The literal's type drives the result.
- A `string` parameter does *not* accept a raw literal "for free" — there's a conversion (5.7). For `string_view` it's a direct bind (5.8).

## Run
    make 5.02
