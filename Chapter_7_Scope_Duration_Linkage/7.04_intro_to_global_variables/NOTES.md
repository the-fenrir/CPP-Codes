# 7.4 — Introduction to global variables

> learncpp.com: https://www.learncpp.com/cpp-tutorial/introduction-to-global-variables/

## Why it matters
Globals exist for the duration of the program and are visible from every function declared after them. They're the simplest way to "share state," which is also why they cause the most damage (see 7.8). You still need to understand them — they're the foundation for `const` globals (fine) and `inline constexpr` globals (the canonical way to share constants, 7.10).

## Key points
- **Scope** = file scope (a.k.a. global namespace scope): from point of declaration to end of the file.
- **Duration** = static: created at program start, destroyed at program end.
- **Linkage** = external by default (non-const) or internal by default (const/constexpr). Linkage is the difference between "the same name across files" and "a separate variable per file"; see 7.6/7.7.
- Globals are **zero-initialized** by default, unlike locals. `int g_count;` at file scope is `0`.
- Convention: prefix global names with `g_` to make their nature obvious at every use site.
- Putting a global inside a `namespace` doesn't change its duration or linkage — it just gives the name a qualifier.

## Code in this folder
- `main.cpp` — a non-const global, a const global, both read and (for the non-const) modified from a function.

## Gotchas
- Initialization order of globals **across translation units is undefined** — the "static initialization order fiasco." If `g_a` in `a.cpp` depends on `g_b` in `b.cpp` at startup, you have a bug that may or may not manifest.
- Globals declared `const` at file scope have *internal* linkage by default — they don't collide across files, which surprises people who expect `extern`-like behavior. See 7.6.

## Run
    make 7.04
