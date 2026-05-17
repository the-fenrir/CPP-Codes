# 5.4 — The as-if rule and compile-time optimization

> learncpp.com: https://www.learncpp.com/cpp-tutorial/the-as-if-rule-and-compile-time-optimization/

## Why it matters
C++ doesn't promise the machine code mirrors your source one statement at a time — it promises only that the program *behaves* as if it did. That's the **as-if rule**, and it's why the compiler can fold `3 + 4` into `7` at compile time, hoist invariant code out of a loop, or skip computing a value you never read. Understanding this is what separates "I wrote `const`" from "this code disappears entirely in release builds."

## Key points
- **As-if rule.** A compiler may make any transformation it wants, as long as the program's *observable behavior* (I/O, volatile accesses, etc.) is unchanged. Whitespace, statement order, and intermediate variables are not observable.
- **Compile-time evaluation** is one consequence: if the compiler can prove an expression's value, it can substitute it. `int x{ 3 + 4 };` becomes `int x{ 7 };` at any reasonable optimization level.
- **Constant folding** = folding constant subexpressions at compile time. Happens to literals automatically; happens to `const`/`constexpr` variables when the compiler can see their definitions.
- **Constant propagation** = replacing a use of a known-constant variable with its value. Enables further folding downstream.
- **Dead-code elimination** = removing code whose result isn't observed. `int unused{ slow_func() };` with no further use may be removed entirely — *unless* `slow_func()` has side effects the compiler can't see through.
- "Compiler might do X" is not the same as "compiler *will* do X." Optimizations are quality-of-implementation. `constexpr` (5.6) is how you *force* compile-time evaluation.

## Code in this folder
- `main.cpp` — small examples showing folding (`3 + 4`), propagation through a `const`, and an unused-result computation the optimizer is free to drop.

## Gotchas
- Side effects break the magic. `std::cout`, file writes, `volatile` reads, calls into another translation unit — the compiler can't elide those even if the result is unused.
- Debug builds (`-O0`) typically *don't* perform these optimizations. Don't benchmark or read disassembly in debug mode and conclude C++ is slow.
- The as-if rule is about behavior, not timing. A loop that runs in 1µs vs. 1ms is still "as-if equivalent."

## Run
    make 5.04
