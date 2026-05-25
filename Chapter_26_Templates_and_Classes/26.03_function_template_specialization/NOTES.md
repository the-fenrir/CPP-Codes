# 26.3 — Function template specialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-template-specialization/

## Why it matters
Sometimes one type wants different behavior from the generic template — `double` should print in scientific notation, `bool` should print `"true"`/`"false"`, etc. Full specialization lets you carve out a single type and give it its own implementation while keeping the same name and signature.

## Key points
- Syntax: `template<> void print<double>(const double&) { … }` — empty `<>`, the specialized type in `<>` after the function name.
- A specialization is **not** an overload. It's a "use this body for this exact instantiation."
- The primary template must be visible before the specialization.
- Specializations are **not implicitly inline**. If you put one in a header it must be marked `inline` (or you'll hit ODR violations across TUs).
- **Prefer plain overloads / non-template functions** over function template specialization. Overloads have nicer signature flexibility and beat specializations in overload resolution.

## Code in this folder
- `main.cpp` — generic `print(const T&)` plus a `double` full-specialization that prints scientifically, and an overload for `bool` that prints `"true"`/`"false"` to show the recommended alternative.

## Gotchas
- A specialization defined in a header without `inline` will silently violate ODR — works in single-TU programs, breaks the moment you have two.
- A non-template overload that matches exactly will be chosen over a specialization. This is why most "I need different behavior for type X" cases should just be an overload.
- You cannot *partially* specialize a function template. Only classes can have partial specializations; for functions you write another overload.

## Run
    make 26.03
