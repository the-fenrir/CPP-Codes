# 17.8 — C-style array decay

> learncpp.com: https://www.learncpp.com/cpp-tutorial/c-style-array-decay/

## Why it matters
The single most surprising rule in C/C++: in almost every context, the name of a C-style array implicitly converts ("decays") to a pointer to its first element. The conversion is silent, sheds the size information, and breaks every "obvious" property you'd want from an array — `sizeof`, range-based `for`, `std::size`, comparison. If you understand decay you understand 80% of legacy-array bugs.

## Key points
- `int arr[5];` — inside the scope where `arr` is declared, `arr` is an array. The moment you pass it, assign it, or do most things with it, it becomes `int*` pointing to `arr[0]`.
- After decay: `sizeof(arr)` becomes `sizeof(int*)` (4 or 8 bytes), not the array size. `std::size(arr)` won't compile. Range-based `for` won't compile.
- Decay happens at: function calls (`f(arr)` — the parameter is `int*`), arithmetic (`arr + 1`), assignment to `int*`, ternary returning `int*`.
- Decay does **not** happen at: `sizeof(arr)`, `&arr` (gives `int(*)[5]`), reference parameters (`void f(int (&arr)[5])`), `decltype(arr)`, `typeid(arr)`.
- Workarounds: pass by reference-to-array (`void f(int (&arr)[5])`, ugly), template on size (`template<size_t N> void f(int (&arr)[N])`), or — the sane answer — use `std::array` or `std::span`.

## Code in this folder
- `main.cpp` — array's `sizeof` before decay, the same array passed to a function and `sizeof` inside (now pointer size), and a templated reference parameter that survives decay.

## Gotchas
- `void f(int arr[5])` looks like it preserves the size; it doesn't. The compiler silently rewrites the signature to `void f(int* arr)`. The `[5]` is documentation only, completely unenforced.
- The compiler may warn about `sizeof(parameter)` if it suspects you're trying to count elements through a decayed pointer.
- `for (int x : someArray)` works only if `someArray` hasn't decayed. The compiler must see the array type.

## Run
    make 17.08
