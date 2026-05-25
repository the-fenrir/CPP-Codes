# 20.1 — Function pointers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/function-pointers/

## Why it matters
Functions live at addresses, just like variables. Once you accept that, "pass the *behavior* as a parameter" becomes a real option: a sort routine takes a comparator, an event loop takes a callback, a table-of-handlers maps codes to actions. Function pointers are the rawest form of that idea — they're what `std::function` and lambdas are built on.

## Key points
- A function name decays to its address: `&foo` and `foo` give the same pointer.
- Pointer syntax is `ReturnType (*name)(ParamTypes...)`. The parentheses around `*name` are required — `int* fn(int)` is a function returning `int*`, not a pointer to a function.
- Call through the pointer with `fn(args)` (preferred) or `(*fn)(args)`; both work.
- Use a type alias to stay sane: `using Cmp = bool(*)(int, int);` then write `Cmp c = greater;`.
- A function passed as a parameter implicitly decays to a function pointer — `void apply(int fn(int), int x)` and `void apply(int (*fn)(int), int x)` are the *same* signature.
- `std::function<Ret(Args...)>` (in `<functional>`) is the modern, type-erased wrapper. Holds plain functions, lambdas with captures, member-function-bound objects — anything callable with that signature. Use it when you need to *store* a callable; use raw function pointers only when you know the callee is a free function.

## Code in this folder
- `main.cpp` — function pointer basics, passing comparators to a generic `selectAndPrint`, and the same job via `std::function`.

## Gotchas
- A raw function pointer **cannot** hold a lambda that captures. Captureless lambdas convert to function pointers; capturing ones don't. Use `std::function` (or `auto` + a template) for those.
- Don't use a function pointer where a template would do — `std::sort` taking a templated comparator inlines the call; a function pointer can't be inlined and is measurably slower in tight loops.
- Default arguments live at the call site, not on the pointer. `int (*fn)(int)` can point at `foo(int x = 0)`, but calling `fn()` is still an error.

## Run
    make 20.01
