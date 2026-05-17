// 3.1 — syntax errors are caught by the compiler; semantic errors are not.
//
// This program compiles cleanly. It's supposed to print the sum 1+2+...+10 = 55.
// It prints something else. Two semantic bugs are hiding in here — see if you
// can spot them before reading the comment at the bottom.
#include <iostream>

int main() {
    int sum;                          // (bug 1) uninitialized — undefined value
    for (int i{ 1 }; i <= 10; ++i)    // (intentionally correct: 1..10 inclusive)
        sum += i;                     // adds to garbage

    std::cout << "sum(1..10) = " << sum << '\n';

    // For contrast, here's the same loop with both bugs fixed:
    int fixed{ 0 };
    for (int i{ 1 }; i <= 10; ++i)
        fixed += i;
    std::cout << "fixed       = " << fixed << '\n';
}

// Bugs:
//   1. `int sum;` left uninitialized. Reading it before assignment is UB; on
//      most systems you'll see a large or negative number — not 55.
//   2. (Subtler variant, not present above but common): writing `i < 10` would
//      stop at i=9 and print 45. Off-by-one is the canonical semantic error.
//
// The compiler with -Wall flags bug 1 ("'sum' is used uninitialized"). It
// CAN'T flag bug 2 because both `<` and `<=` are valid C++ — only the
// programmer knows which one was intended.
