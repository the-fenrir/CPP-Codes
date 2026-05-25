// 22.2 — Overloading on lvalue vs rvalue references.
//
// Three overloads, three different binding rules. The interesting case is
// the last one: a *named* rvalue reference (`r` inside main) is itself an
// lvalue, so f(r) takes the int& overload — not the int&& one.
#include <iostream>
#include <utility>

void f(int&)             { std::cout << "  int&        (modifiable lvalue)\n"; }
void f(const int&)       { std::cout << "  const int&  (any lvalue, or rvalue fallback)\n"; }
void f(int&&)            { std::cout << "  int&&       (rvalue)\n"; }

int makeInt() { return 42; }

int main() {
    int x{ 5 };
    const int cx{ 7 };

    std::cout << "f(x):           "; f(x);           // lvalue → int&
    std::cout << "f(cx):          "; f(cx);          // const lvalue → const int&
    std::cout << "f(10):          "; f(10);          // prvalue literal → int&&
    std::cout << "f(x + 1):       "; f(x + 1);       // prvalue expression → int&&
    std::cout << "f(makeInt()):   "; f(makeInt());   // prvalue (returned by value) → int&&

    int&& r = 99;                                    // r is a named rvalue ref
    std::cout << "f(r):           "; f(r);           // r has a name → lvalue → int&
    std::cout << "f(std::move(r)):"; f(std::move(r));// cast back to rvalue → int&&
}
