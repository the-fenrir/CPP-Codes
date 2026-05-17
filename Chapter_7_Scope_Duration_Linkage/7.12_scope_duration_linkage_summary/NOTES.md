# 7.12 — Scope, duration, and linkage summary

> learncpp.com: https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/

## Why it matters
The three properties are **independent**. Every identifier has all three, and almost every C++ storage rule is some combination. Once you can recite "scope/duration/linkage" for any declaration on sight, the rest of the language's storage rules stop surprising you.

## Key points

### Scope — where the name is *visible*
- **Block scope**: locals; from declaration to closing `}`.
- **Namespace (file) scope**: anything at namespace level (including the global namespace); from declaration to end of file.
- **Class scope**: members of a class; reached via `obj.x` / `T::x`.

### Duration — when the storage *lives*
- **Automatic**: stack-allocated locals; created on entry, destroyed at `}`.
- **Static**: globals, static locals, `inline` variables; created at (or before) first use, destroyed at program end.
- **Dynamic**: `new`/`new[]` allocations; live until `delete`/`delete[]`.
- **Thread**: `thread_local` storage; per-thread copy, lives with the thread.

### Linkage — whether the same name *means the same entity* across TUs
- **No linkage**: locals, function parameters.
- **Internal linkage**: file-scope `static` entities, `const`/`constexpr` globals (by default), entities in an unnamed namespace.
- **External linkage**: non-const globals, free functions, `inline` variables, `extern const` globals.

### Common combos you actually see

| Declaration | Scope | Duration | Linkage |
|---|---|---|---|
| `int x;` inside a function | block | automatic | none |
| `static int s_x;` inside a function | block | static | none |
| `int g_x;` at file scope | namespace | static | external |
| `static int g_x;` at file scope | namespace | static | internal |
| `const int g_x{};` at file scope | namespace | static | internal |
| `inline constexpr int g_x{};` in header | namespace | static | external (one defn) |
| `extern int g_x;` (declaration) | namespace | static | external (refers elsewhere) |

## Code in this folder
- `main.cpp` — one example of each row above, with comments labeling its trio.

## Gotchas
- "Static" is overloaded three ways: file-scope `static` (internal linkage), function-scope `static` (static duration), class-scope `static` (class-wide member). Same keyword, three meanings.
- Linkage applies to **names**, not values. Two TUs each with `static int s_x;` have two separate variables — there's no linkage to connect them.

## Run
    make 7.12
