// 12.2 — value categories in practice.
#include <iostream>

int  return_by_value()      { return 5; }   // call expression is rvalue
int& return_by_reference()  { static int s{ 10 }; return s; } // call expression is lvalue

int main() {
    int x { 5 };

    // ── lvalues ───────────────────────────────────────────────────
    x = 10;                       // x is a (modifiable) lvalue
    &x;                           // can take its address
    int& r{ x }; (void)r;         // can bind a non-const lvalue ref to it
    return_by_reference() = 42;   // function call is an lvalue → assignable
    std::cout << "after assigning to return_by_reference(): "
              << return_by_reference() << '\n';

    // ── rvalues ───────────────────────────────────────────────────
    int y{ x + 1 };               // x+1 is an rvalue (transient)
    y = return_by_value();        // call result is an rvalue
    (void)y;
    // 5 = x;                     // ERROR: literal 5 is rvalue — no left side
    // int& r2 { x + 1 };         // ERROR: rvalue can't bind to non-const lvalue ref
    // int& r3 { 5 };             // ERROR: same reason
    const int& r4 { x + 1 };      // OK: const-ref extends the temporary's lifetime
    std::cout << "r4 (bound to rvalue x+1) = " << r4 << '\n';

    // ── const lvalues are still lvalues, but not modifiable ───────
    const int c{ 7 };
    // c = 8;                     // ERROR: c is an lvalue but not modifiable
    std::cout << "c = " << c << " (lvalue, just not modifiable)\n";
}
