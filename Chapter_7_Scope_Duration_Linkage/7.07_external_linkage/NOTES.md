# 7.7 — External linkage and variable forward declarations

> learncpp.com: https://www.learncpp.com/cpp-tutorial/external-linkage-and-variable-forward-declarations/

## Why it matters
*External* linkage means the linker can match a use in one translation unit to a definition in another. This is how multi-file programs share functions and (occasionally) globals. The trick is the same as for functions: **declare** in every TU that uses the name; **define** in exactly one. For globals, the declaration form uses `extern`.

## Key points
- Non-const globals at file scope have external linkage by default.
- Free functions have external linkage by default.
- To *use* an externally-linked global from another file, you need a **variable forward declaration**: `extern int g_x;` — note: no initializer, that would make it a definition.
- To give a `const`/`constexpr` global external linkage explicitly (overriding the internal default), write `extern const int g_x{ 5 };` in one TU and `extern const int g_x;` in others. (Spoiler: don't do this for sharing constants — use 7.10's `inline constexpr` instead.)
- One Definition Rule: exactly one **definition** per variable across the whole program. Many declarations are fine.

## Code in this folder
This is a **multi-file** lesson.

- `globals.h` — `extern` *declarations* visible to every TU that includes it.
- `globals.cpp` — the one **definition** of each global.
- `main.cpp` — reads them via the header.

## Gotchas
- `extern int x;` is a *declaration*. `int x;` is a *definition* (and an extern one by default). `extern int x{ 5 };` is a definition *with* an initializer — same effect as plain `int x{ 5 };`.
- Two `.cpp` files each writing `int g_x{};` at file scope is two definitions of the same external name ⇒ linker error. The header pattern (declare in `.h`, define in one `.cpp`) prevents that.
- For *constants*, this whole dance is unnecessary in modern C++: just use `inline constexpr` in a header (7.9 / 7.10). The `extern const` mechanism still exists, mostly for legacy code.

## Run
    make 7.07
