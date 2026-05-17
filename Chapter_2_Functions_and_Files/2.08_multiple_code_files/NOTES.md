# 2.8 — Programs with multiple code files

> learncpp.com: https://www.learncpp.com/cpp-tutorial/programs-with-multiple-code-files/

## Why it matters
Real programs don't fit in one file. Each `.cpp` is compiled independently into an object file (a **translation unit**), and the linker stitches them together. This is also why forward declarations exist — they're how one TU tells the compiler about symbols defined in another.

## Key points
- Each `.cpp` is compiled separately. The compiler only sees what's in (or `#include`d into) that single file.
- To call a function in another `.cpp` from this `.cpp`, **forward declare** it here. The linker resolves the actual call at link time.
- Build line conceptually: `g++ main.cpp add.cpp -o prog`. The Makefile in this repo auto-links all `.cpp` files in a lesson folder when a header is present.
- Names defined at file scope are external by default (with caveats: `static` / unnamed namespaces make them TU-local — covered later).
- Sharing class definitions, inline functions, templates, and `constexpr` across TUs is the job of *header files* (2.11).

## Code in this folder
- `add.cpp` — defines `add()`.
- `add.h` — declares `add()` so the Makefile's "header present ⇒ link all .cpp" mode kicks in.
- `main.cpp` — uses `add()` via the header. (You *could* forward-declare `add` directly in `main.cpp` instead; the header is shown because it's the actually-used pattern.)

## Gotchas
- Forgetting to pass `add.cpp` to the linker = "undefined reference to `add(int, int)`" — a *link* error, not a compile error.
- Defining the same function in two `.cpp` files violates ODR; both compile fine, the link breaks.
- A prototype in `main.cpp` that disagrees with the definition in `add.cpp` won't be caught by the compiler — the symbols may still link, but the call is undefined behavior.

## Run
    make 2.08
