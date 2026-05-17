# 11.10 — Using function templates in multiple files

> learncpp.com: https://www.learncpp.com/cpp-tutorial/using-function-templates-in-multiple-files/

## Why it matters
Normal functions split cleanly: declaration in `.h`, definition in `.cpp`. Templates **don't**. Because instantiation happens per call site, the compiler must see the entire template body wherever it's used. Put a template body in a `.cpp` and only its declaration in the header, and you'll get a *linker* error — the instantiation that the caller needs was never generated.

## Key points
- The compiler instantiates a template only when it sees both the body **and** the type arguments. The caller's `.cpp` provides the type arguments; the body has to be visible too.
- **Conclusion: templates live in headers.** Including the header pulls in the full body; each translation unit instantiates what it needs; the linker deduplicates identical instantiations (they're `inline` by language rule).
- Alternatives — usually not worth it:
  - **Explicit instantiation** in a `.cpp`: `template int max<int>(int, int);`. The template body still has to live somewhere — typically still a header — but you force one TU to materialize the symbol so others can link to it. Used when you want to hide the body or cut compile time for a closed set of types.
- A template-only header has no `.cpp` of its own. The "multi-file" part here is the header plus the caller's `main.cpp`.

## Code in this folder
- `max.h` — function template `my_max<T>` lives entirely in the header.
- `main.cpp` — includes `max.h` and instantiates `my_max<int>` and `my_max<double>`.

The repo Makefile compiles `*.cpp` together; this folder has only `main.cpp` plus the header, which is the typical real-world template layout.

## Gotchas
- Linker error `undefined reference to my_max<int>(int, int)` is the classic symptom of putting the body in a `.cpp`. Move the body to the header.
- Member functions of class templates follow the same rule (see 15.5) — keep them in the header.
- Putting `inline` on a template function definition is redundant — template definitions are already exempt from the ODR for identical instantiations.

## Run
    make 11.10
