# 11.7 — Function template instantiation

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-template-instantiation/

## Why it matters
A template by itself produces zero code. The compiler generates a concrete function — an **instantiation** — the first time you use the template with a specific type combination. Once you see this clearly, three things stop being mysterious: why templates live in headers, why `static` variables inside a template behave per-type, and why non-template overloads can win against a template.

## Key points
- **Implicit instantiation**: `max(1, 2)` — compiler picks `T = int`, generates `max<int>` if not already present.
- **Explicit instantiation**: `template int max<int>(int, int);` — force generation in a specific translation unit (covered for completeness; 11.10 is where this matters).
- **Template argument deduction** does **not** perform conversions. `max(1, 2.0)` fails: `T` can't be both `int` and `double`. Fixes: `max<double>(1, 2.0)`, or `max(1.0, 2.0)`, or two template parameters (11.8).
- Each distinct `T` produces a **separate function** with separate `static` locals — that's why quiz Q3's `count<int>` and `count<double>` each have their own counter.
- Overload resolution with templates: in a tie between a non-template overload and a template instantiation that requires no conversions, the **non-template wins**. That's quiz Q4: `foo(int)` (non-template) beats `foo<int>(int)` for `foo(1)`.

## Code in this folder
- `main.cpp` — counter template demonstrating per-type `static`, plus a non-template-vs-template resolution example.

## Gotchas
- Compile errors from templates often point inside the standard library — read upward until you find the line in *your* code that triggered the instantiation.
- Header-only consequence (11.10): the template body must be visible to every translation unit that instantiates it.
- `T*` and `T` are different types; `count<int*>(&x)` and `count<int>(1)` give different counters.

## Run
    make 11.07
