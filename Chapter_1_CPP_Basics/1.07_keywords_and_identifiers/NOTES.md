# 1.7 — Keywords and naming identifiers

> learncpp.com: https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/

## Why it matters
You name variables, functions, and types constantly. The rules for what's a *legal* name are simple, but the conventions around *good* names are what separate readable code from a wall of mush. Names are the cheapest documentation you'll ever write.

## Key points
- **Keywords** are reserved words the language owns (`int`, `return`, `if`, `class`, ...). You can't use them as identifiers.
- **Identifier rules:**
  - Made of letters, digits, and underscores.
  - Must not start with a digit.
  - Case-sensitive: `count` and `Count` are different names.
  - Cannot be a keyword.
  - Cannot start with an underscore in the global namespace (those are reserved for the implementation).
- **Conventions** (not rules):
  - Variables and functions: `snake_case` or `camelCase` — pick one per project and stick with it.
  - Types: `PascalCase` is common.
  - Don't use leading underscores or all-caps for ordinary names (all-caps is conventionally for macros).
  - Names should describe intent (`retry_count`, not `n`).

## Code in this folder
- `main.cpp` — a few well-named and badly-named variables side by side.

## Gotchas
- A long name is fine. A short, unclear name (`tmp`, `data`, `x` outside a tight loop) is not.
- Identifiers starting with `_` followed by an uppercase letter, or containing `__`, are *reserved by the implementation* anywhere in the program — don't define them.

## Run
    make 1.07
