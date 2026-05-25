# 26.1 — Template classes

> learncpp.com: https://www.learncpp.com/cpp-tutorial/template-classes/

## Why it matters
Function templates eliminate duplicated functions; class templates eliminate duplicated *containers*. `std::vector`, `std::array`, `std::map` — none of them could exist without this feature. Once you can write `Array<T>`, the entire STL stops being a black box.

## Key points
- `template <typename T> class Foo { … };`. Inside the class, `T` is just a type name.
- Each instantiation (`Foo<int>`, `Foo<double>`) is a **separate type**, separately compiled.
- Out-of-line member definitions repeat the template header and qualify the class with `<T>`:
  ```cpp
  template <typename T>
  T& Array<T>::operator[](int index) { … }
  ```
- Class template **bodies and member definitions must be visible at every use site** — split-into-`.cpp` doesn't work because the compiler instantiates per translation unit.
- Three options when files get large: (1) put everything in the header (default), (2) `#include` an `.inl` from the header, (3) explicit instantiation in one TU (`template class Array<int>;`).

## Code in this folder
- `main.cpp` — `Array<T>` with `operator[]`, a templated member function defined out-of-line, and two instantiations (`int`, `double`) to show that they're distinct types.

## Gotchas
- Linker errors of the form "undefined reference to `Foo<int>::bar()`" almost always mean the definition lives in a `.cpp` the current TU never saw. Move it to the header.
- Every distinct `T` produces a fresh copy of every member function used → binary bloat if you template trivially.
- The class name inside an out-of-line definition is `Foo<T>`, not `Foo`. The plain `Foo` (the *injected class name*) only works inside the class body.

## Run
    make 26.01
