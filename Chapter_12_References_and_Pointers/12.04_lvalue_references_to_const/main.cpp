// 12.4 — const lvalue references bind to almost anything readable.
#include <iostream>

int main() {
    int x { 5 };

    // Bind to a regular (modifiable) lvalue:
    const int& r1 { x };
    std::cout << "r1 (bound to x) = " << r1 << '\n';
    // r1 = 10;          // ERROR: const through r1
    x = 10;              // OK: x itself is not const
    std::cout << "after x = 10 → r1 = " << r1 << " (sees the change)\n";

    // Bind to a const object — required to be const ref:
    const int c { 7 };
    const int& r2 { c };
    // int& bad { c };   // ERROR: would discard const
    std::cout << "r2 (bound to const c) = " << r2 << '\n';

    // Bind to an rvalue / literal — lifetime extension:
    const int& r3 { 42 };
    std::cout << "r3 (bound to literal) = " << r3 << '\n';

    // Bind to a temporary of a different type (implicit conversion → temp int):
    double d { 3.7 };
    const int& r4 { static_cast<int>(d) }; // explicit; relying on implicit is a footgun
    std::cout << "r4 (bound to temp from d) = " << r4
              << "  (does NOT follow later changes to d)\n";
    d = 99.9;
    std::cout << "after d = 99.9 → r4 = " << r4 << '\n';
}
