// 11.3 — overload resolution: exact match, promotion, conversion, ambiguity.
#include <iostream>

void print(int x)    { std::cout << "int "    << x << '\n'; }
void print(double x) { std::cout << "double " << x << '\n'; }

// ── Ambiguity demo (commented so the file still compiles) ─────
// Uncomment the second pair AND the call below to see the error.
//
//     void mix(long);
//     void mix(double);
//     mix(5);   // error: int → long and int → double are both
//               // "standard conversion"; neither is better.

int main() {
    print(42);            // exact match → int overload
    short s{ 5 };
    print(s);             // promotion short → int → int overload (NOT double)
    print(3.14f);         // promotion float → double → double overload

    // print(7L);          // would be ambiguous: long → int and long → double are
                           //   both "standard conversion" tier — same rank, no winner.
                           //   Cast to pick one:
    print(static_cast<int>(7L));
}
