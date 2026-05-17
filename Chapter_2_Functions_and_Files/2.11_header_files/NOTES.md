# 2.11 — Header files

> learncpp.com: https://www.learncpp.com/cpp-tutorial/header-files/

## Why it matters
2.7 introduced forward declarations and 2.8 used them across files. That works, but doesn't scale — every caller would need to keep its private copy of every prototype in sync with every definition. **Header files** centralize the declarations: write them once, `#include` them everywhere they're needed.

## Key points
- A header (`.h`) contains *declarations*: function prototypes, class definitions, `constexpr` constants, `inline` functions, templates.
- A header is `#include`d — that's literally text substitution by the preprocessor.
- A `.cpp` *defines* the functions it declared; other `.cpp` files include the header to *use* them.
- System headers: `#include <iostream>`. User headers: `#include "math_utils.h"`. The `<...>` form skips the current directory.
- Headers should be **self-contained**: anything they reference is included or forward-declared inside the header.
- A header should not define non-inline non-template functions or non-inline variables at file scope — that violates ODR if included from more than one TU.

## Code in this folder
- `add.h` — declares `add()`.
- `add.cpp` — defines `add()`.
- `main.cpp` — `#include "add.h"` and calls it.

The Makefile sees the `.h` and links both `.cpp`s into one binary.

## Gotchas
- A header that defines a free function `int add(int, int) { ... }` (not inline, not template) will compile fine, but the *linker* will reject any program that includes it in two TUs.
- Don't include `.cpp` files. Ever. Include the `.h`, link the `.cpp`.
- `#include "foo.h"` searches the current directory first; `<foo.h>` doesn't. Convention: quotes for your code, angle brackets for libraries.

## Run
    make 2.11
