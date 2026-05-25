# 21.8 — Overloading `++` and `--`

> learncpp.com: https://www.learncpp.com/cpp-tutorial/overloading-the-increment-and-decrement-operators/

## Why it matters
Pre-increment (`++x`) returns a reference to the modified object; post-increment (`x++`) returns the **old** value by value. Both are spelled `operator++` — the language disambiguates with a fake `int` parameter on the postfix version. This is the single dirtiest corner of operator overloading; just memorise the shapes.

## Key points
- **Prefix** (member): `T& T::operator++()` — mutate `*this`, return `*this`.
- **Postfix** (member): `T T::operator++(int)` — save old, mutate `*this`, return the **old copy**. The `int` parameter is a dummy used only to distinguish the overload; it's always `0`.
- Implement postfix in terms of prefix. Don't duplicate the increment logic.
- Same shapes for `operator--`.
- Prefer prefix in your own code: postfix forces an extra copy of the old value.

## Code in this folder
- `main.cpp` — a `Digit` (0–9 with wraparound) showing both prefix and postfix `++` / `--`.

## Gotchas
- Returning `*this` from postfix is a bug: it gives back the *new* value, not the old.
- The dummy `int` parameter is unnamed and unused; some compilers warn. Either name it (`int /*postfix*/`) or live with it.
- If postfix calls prefix, the temporary it returns gets RVO'd in most cases. Don't try to optimise it away with weird tricks.

## Run
    make 21.08
