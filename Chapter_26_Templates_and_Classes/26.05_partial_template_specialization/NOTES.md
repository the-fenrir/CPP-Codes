# 26.5 — Partial template specialization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/partial-template-specialization/

## Why it matters
Full specialization pins *every* template parameter — that's enough for `Storage8<bool>`, but useless for "anything that's a `StaticArray<char, N>` for any `N`." Partial specialization lets you pin *some* parameters while leaving others free. This is the mechanism behind a huge chunk of the standard library's metaprogramming (`std::is_pointer`, `std::remove_reference`, etc.) and the pointer-handling trick we'll see in 26.6.

## Key points
- Syntax: a template header listing the *still-free* parameters, then the class name with a partially-pinned argument list:
  ```cpp
  template <int N>
  class StaticArray<char, N> { … };
  ```
- The compiler picks the **most specialized** matching template at instantiation time. `StaticArray<char, 12>` prefers the char partial specialization over the primary `StaticArray<T, N>`.
- **Functions cannot be partially specialized.** What looks like one is always a regular overload. For functions, write another overload instead.
- You can partially specialize on shape (`Foo<T*>`, `Foo<T, T>`, `Foo<std::vector<T>>`, …), not just on individual parameters.

## Code in this folder
- `main.cpp` — `StaticArray<T, N>` with a partial specialization for `T = char` that adds a `print()` that treats the buffer as a C-string. Demonstrates that the same call site picks different bodies based on `T`.

## Gotchas
- Forgetting that the *partially* free parameters are repeated in the template header is the #1 syntax error here.
- Two partial specializations that both match equally well are an ambiguity error — there's no automatic "tie-break."
- If you reach for partial specialization of a function template, stop and write an overload instead.

## Run
    make 26.05
