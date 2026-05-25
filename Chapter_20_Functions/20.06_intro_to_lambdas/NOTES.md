# 20.6 — Introduction to lambdas (anonymous functions)

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/

## Why it matters
A lambda is a function you can write *inline*, at the call site. Before lambdas, customizing a generic algorithm meant writing a named function (or a "functor" struct with `operator()`) elsewhere in the file. Lambdas let the predicate live next to the call that uses it, where the reader actually needs to see it. Once you use `std::find_if(v.begin(), v.end(), [](int x){ return x > 10; })` a few times, you stop wanting to go back.

## Key points
- Syntax: `[captures](params) -> ReturnType { body }`. Most parts are optional:
  - `[]` — capture clause (always required, even if empty).
  - `(params)` — parameter list. C++14+: can be omitted if there are no parameters.
  - `-> ReturnType` — return type. Usually deduced; specify when the deduction would be wrong or ambiguous.
- A lambda's *type* is a unique, unnamed compiler-generated class. Store it with `auto`. To store across boundaries where the exact type is unhelpful, use `std::function<Sig>`.
- A *captureless* lambda is implicitly convertible to a plain function pointer with the same signature. A capturing one is not.
- Parameters can be `auto` (since C++14) — that's a *generic lambda*; internally it's a templated `operator()`.
- `mutable` after the parameter list lets the lambda modify its captured-by-value copies (next lesson goes deep on this).

## Code in this folder
- `main.cpp` — minimal lambda, lambda passed to `std::sort` / `std::count_if`, generic lambda with `auto` parameter, and the captureless-lambda-to-function-pointer conversion.

## Gotchas
- Each lambda expression yields a *distinct* type — even two textually identical lambdas have different types. That's why you need `auto` (or `std::function`) to store them.
- A non-capturing lambda is `constexpr`-capable in C++17+; capturing ones need explicit `constexpr` and qualifying conditions.
- `[](auto x){ return x + x; }` is a function *template*, so it's instantiated per call type — fine, but it does mean compile-time cost scales with the number of distinct argument types.

## Run
    make 20.06
