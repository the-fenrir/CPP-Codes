// 11.2 — what counts as a different overload, and what doesn't.
#include <iostream>

// ── Differentiated by parameter count ─────────────────────────
void f(int)        { std::cout << "f(int)\n"; }
void f(int, int)   { std::cout << "f(int,int)\n"; }

// ── Differentiated by parameter type ──────────────────────────
void g(int)        { std::cout << "g(int)\n"; }
void g(double)     { std::cout << "g(double)\n"; }

// ── Low-level const IS part of the type ───────────────────────
void h(int*)       { std::cout << "h(int*)\n"; }
void h(const int*) { std::cout << "h(const int*)\n"; }

// ── NOT differentiated: top-level const on a by-value param ───
// Uncommenting the second declaration is a redefinition error:
//     void k(int)       {}
//     void k(const int) {}   // same overload as void k(int)

// ── NOT differentiated: return type alone ─────────────────────
//     int    m(int);
//     double m(int);         // error: differs only in return type

int main() {
    f(1);
    f(1, 2);
    g(1);
    g(1.5);

    int x = 7;
    const int y = 7;
    h(&x);     // int*
    h(&y);     // const int*
}
