// Chapter 2 quiz solutions.
//   Q1: single-file readNumber/writeAnswer/main
//   Q2: same, split into io.cpp + main.cpp with forward declarations
//   Q3: same, but with io.h header replacing the forward declarations
//
// Why one file here instead of three?
//   The runtime behavior is identical across Q1/Q2/Q3 — the exercise is
//   structural. Lessons 2.08 and 2.11 in this chapter already demonstrate
//   the multi-file layout in code; reproducing that here would just duplicate
//   it. Instead, this file contains the Q1 solution and a long comment block
//   describing what Q2 and Q3 would look like, with the design rationale.
//
// Why hardcoded inputs?
//   `make 2.x` is run by the build system, not a human. A program that blocks
//   on std::cin would hang the build. So readNumber() checks whether stdin
//   is a terminal: interactive → prompt + read; non-interactive → return a
//   canned value. This keeps the function shape faithful to the spec while
//   still letting CI / `make` complete.
#include <iostream>
#include <unistd.h>            // isatty, STDIN_FILENO

// ── Q1: single-file solution ────────────────────────────────────────
//
// Design notes:
//  • readNumber() returns int rather than taking an output parameter — value
//    flow is easier to follow when each function has one output (its return).
//  • writeAnswer() takes its parameter by value: int is cheap to copy and
//    the function doesn't need to mutate the caller's copy.
//  • main() composes: read, read, add, write. Each step is a sentence.
//  • The DRY argument from 2.6 is exactly what motivates readNumber() — we
//    need to read a number twice, so we factor out the prompt+read+return.
int readNumber() {
    // Build-friendly fallback: only prompt if a real user is at the keyboard.
    static int fakeInputs[] = { 3, 4 };
    static int fakeIndex{ 0 };

    if (!isatty(STDIN_FILENO)) {
        const int v{ fakeInputs[fakeIndex++ % 2] };
        std::cout << "Enter an integer: " << v << "  (non-interactive)\n";
        return v;
    }

    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;
    return x;
}

void writeAnswer(int x) {
    std::cout << "The answer is: " << x << '\n';
}

int main() {
    const int a{ readNumber() };
    const int b{ readNumber() };
    writeAnswer(a + b);
}

// ── Q2: two-file version ────────────────────────────────────────────
//
// Layout:
//   io.cpp
//       #include <iostream>
//       int readNumber()        { /* same body */ }
//       void writeAnswer(int x) { /* same body */ }
//
//   main.cpp
//       int  readNumber();           // forward declaration
//       void writeAnswer(int x);     // forward declaration
//       int main() { /* same body */ }
//
// Build:  g++ -std=c++20 main.cpp io.cpp -o prog
//
// Why this is better than Q1:
//   readNumber/writeAnswer are I/O plumbing; main() is business logic.
//   Putting them in different TUs lets you recompile main.cpp without
//   recompiling io.cpp (and vice versa). For a 2-function program that
//   barely matters; for a real codebase it matters a lot.
//
// Why this is *worse* than Q3:
//   The forward declarations in main.cpp duplicate the function signatures.
//   If io.cpp changes (e.g. readNumber starts returning long), main.cpp's
//   prototype is now wrong — and the compiler can't catch it, because
//   main.cpp is compiled separately from io.cpp. The link might still
//   succeed and call the function with the wrong calling convention.
//   That's a footgun a header file would eliminate.

// ── Q3: header-file version ─────────────────────────────────────────
//
// Layout:
//   io.h
//       #ifndef CPP_CODES_CH2_QUIZ_IO_H
//       #define CPP_CODES_CH2_QUIZ_IO_H
//       int  readNumber();
//       void writeAnswer(int x);
//       #endif
//
//   io.cpp
//       #include "io.h"            // ensures its definitions match the header
//       /* same bodies as Q2 */
//
//   main.cpp
//       #include "io.h"            // replaces the two forward declarations
//       int main() { /* same body */ }
//
// Build:  g++ -std=c++20 main.cpp io.cpp -o prog
//
// Why this is the right shape:
//   1. Single source of truth for the signatures: io.h. If readNumber()
//      changes signature, both io.cpp and main.cpp see the new declaration
//      via #include, and *any* mismatch is a compile error in io.cpp itself
//      (since io.cpp includes io.h and the definition must match).
//   2. Cheap to add a third caller: a new file just #include "io.h". With
//      forward declarations (Q2), every new caller copies the prototypes.
//   3. Header guard prevents double-inclusion as soon as any other header
//      starts pulling io.h in transitively.
//   4. The header *also* documents the module's public surface — readers can
//      open io.h to see what io.cpp offers, without scanning the .cpp.
