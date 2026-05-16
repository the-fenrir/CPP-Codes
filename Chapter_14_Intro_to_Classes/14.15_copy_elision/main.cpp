// 14.15 — watch (or don't watch) the copy constructor fire.
#include <iostream>

struct Loud {
    int v;
    Loud(int x)              : v{ x } { std::cout << "  ctor(" << v << ")\n"; }
    Loud(const Loud& o)      : v{ o.v } { std::cout << "  copy("  << v << ")\n"; }
    ~Loud()                                { std::cout << "  ~"     << v << '\n'; }
};

Loud makeProvalue()      { return Loud{ 1 }; }   // mandatory elision
Loud makeNamed()         { Loud x{ 2 }; return x; } // NRVO (optional but typical)

int main() {
    std::cout << "1) direct init from prvalue:\n";
    Loud a{ makeProvalue() };   // expect: ctor(1), then destruction at end of main

    std::cout << "2) copy init from prvalue:\n";
    Loud b = makeProvalue();    // same — mandatory elision

    std::cout << "3) NRVO from named local:\n";
    Loud c = makeNamed();       // usually elided; not standard-guaranteed

    std::cout << "4) explicit copy of named lvalue:\n";
    Loud d = a;                 // NOT elided — copy ctor fires.
}
