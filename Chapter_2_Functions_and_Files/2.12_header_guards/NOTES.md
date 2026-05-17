# 2.12 — Header guards

> learncpp.com: https://www.learncpp.com/cpp-tutorial/header-guards/

## Why it matters
Because `#include` is textual paste, if `a.h` includes `b.h`, and `main.cpp` includes both, `b.h`'s contents end up in the TU *twice*. For a header with only function declarations that's harmless; for one with a class or struct definition, it's a compile error (redefinition). Header guards make headers idempotent — including them N times is the same as including them once.

## Key points
- The classic guard: wrap the header in `#ifndef MY_HEADER_H` / `#define MY_HEADER_H` / `#endif`.
- The modern alternative: `#pragma once` (non-standard but supported by every mainstream compiler). Used throughout this repo.
- Guards prevent **multiple inclusion in the same TU** — they do *not* solve ODR violations across multiple TUs.
- Guard macro names should be unique. Convention: `PROJECT_PATH_FILE_H`. A clash silently disables one of the headers.

## Code in this folder
- `widget.h` — uses the classic `#ifndef` / `#define` / `#endif` style so you can see the pattern.
- `gadget.h` — uses `#pragma once`.
- `main.cpp` — includes both, and includes `widget.h` twice via a transitive chain (through `gadget.h`) to prove the guard works.
- `widget.cpp`, `gadget.cpp` — implementations.

## Gotchas
- Two unrelated headers reusing the same guard macro = the second one is silently skipped. `MY_H` is a bad choice; `PROJECT_MODULE_FILE_H` is better.
- Header guards don't protect against ODR: defining a non-inline function in a header still breaks the link.
- `#pragma once` works on filesystem identity; symbolic links and copies of the same header may defeat it. Standard `#ifndef` guards work on macro identity.

## Run
    make 2.12
