// 12.3 — lvalue references: aliasing and the "ref = other doesn't rebind" trap.
#include <iostream>

int main() {
    int x { 5 };
    int y { 99 };

    int& ref { x };               // ref is now another name for x
    std::cout << "x   = " << x   << ", ref = " << ref << '\n';

    ref = 10;                     // modifies x through ref
    std::cout << "after ref = 10 → x = " << x << '\n';

    // The classic trap: this does NOT rebind ref to y.
    // It assigns y's value (99) into the object ref refers to (x).
    ref = y;
    std::cout << "after ref = y  → x = " << x
              << ", y = " << y << ", ref = " << ref << '\n';

    y = 1234;                     // ref does not follow y
    std::cout << "after y = 1234 → ref = " << ref
              << " (still bound to x, which is unchanged)\n";

    // Addresses confirm the binding:
    std::cout << "&x   = " << &x   << '\n';
    std::cout << "&ref = " << &ref << " (same as &x — ref *is* x)\n";
    std::cout << "&y   = " << &y   << '\n';
}
