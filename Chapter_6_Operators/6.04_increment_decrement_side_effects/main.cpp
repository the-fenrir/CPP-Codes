// 6.4 — prefix vs. postfix, plus a side-effect cautionary note.
#include <iostream>

int main() {
    // ── prefix: increment, then read ────────────────────────────
    int a{ 5 };
    int pre = ++a;
    std::cout << "++a: a=" << a << " pre=" << pre << "   // both 6\n";

    // ── postfix: read, then increment ───────────────────────────
    int b{ 5 };
    int post = b++;
    std::cout << "b++: b=" << b << " post=" << post << "   // b=6, post=5\n";

    // ── safe use: one side effect per statement ────────────────
    int i{ 0 };
    std::cout << "i = " << i << '\n';
    ++i;
    std::cout << "i = " << i << '\n';
    ++i;
    std::cout << "i = " << i << '\n';

    // ── DO NOT WRITE: int bad = i++ + ++i;  // undefined behavior
    //                 std::cout << i << " " << ++i;       // same: UB / unspecified
    //                 foo(i, ++i);                         // same.
    //
    // If you find yourself reaching for one of those, just break it into
    // multiple statements. Code that needs cleverness here is code that's
    // already wrong.
}
