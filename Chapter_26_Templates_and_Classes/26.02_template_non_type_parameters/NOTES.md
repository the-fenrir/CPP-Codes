# 26.2 — Template non-type parameters

> learncpp.com: https://www.learncpp.com/cpp-tutorial/template-non-type-parameters/

## Why it matters
Up to now every template parameter has been a *type* (`T`). A **non-type template parameter** (NTTP) is a compile-time *value* — usually an integer. That's how `std::array<int, 5>` encodes its size in the type itself, which means the size is known at compile time, the storage can live on the stack, and indexing can be bounds-checked statically.

## Key points
- Syntax mixes freely with type parameters: `template <typename T, std::size_t N>`.
- NTTPs must be **compile-time constants** at the call site — `StaticArray<int, n>` with a runtime `n` fails to compile.
- Allowed NTTP types: integral, enum, pointer/reference to object or function, member pointer, `std::nullptr_t`, and (C++20+) floating-point and literal class types.
- Different NTTP values produce *different types*: `StaticArray<int, 4>` and `StaticArray<int, 5>` share nothing.
- Carrying size in the type ⇒ no heap allocation, `sizeof` is meaningful, and the compiler can unroll/inline aggressively.

## Code in this folder
- `main.cpp` — `StaticArray<T, N>` storing a stack-allocated `T[N]`, plus a deliberate static-size mismatch shown via `static_assert`.

## Gotchas
- "Template argument 2 is not a constant expression" — you tried to pass a runtime variable. Use `constexpr` for the size, or switch to a runtime container.
- Two instantiations with different `N` cannot be assigned to each other, which trips people coming from dynamic containers.
- C++20 added floating-point NTTPs, but pre-C++20 compilers reject `template <double X>`. Stay integral unless you really need it.

## Run
    make 26.02
