// 12.7 — pointers: address-of, dereference, rebind.
#include <iostream>

int main() {
    int x { 5 };
    int y { 99 };

    int* p { &x };               // p holds x's address
    std::cout << "x  = " << x  << ",  &x = " << &x  << '\n';
    std::cout << "p  = " << p  << " (== &x),  *p = " << *p << '\n';
    std::cout << "&p = " << &p << " (pointer has its own storage)\n";

    *p = 10;                     // modify x through p
    std::cout << "after *p = 10 → x = " << x << '\n';

    p = &y;                      // REBIND p to point at y (compare ref: not possible)
    std::cout << "after p = &y → *p = " << *p << ", y = " << y << '\n';
    *p = 1234;
    std::cout << "after *p = 1234 → y = " << y << ", x = " << x << " (untouched)\n";

    // Sizes:
    std::cout << "sizeof(int)  = " << sizeof(int)  << '\n';
    std::cout << "sizeof(int*) = " << sizeof(int*) << "  (pointer width)\n";

    // Pointer in a boolean context:
    if (p) std::cout << "p is non-null\n";

    // Footguns shown in comments only:
    // int* bad;        // uninitialized — *bad is UB
    // int* z { &5 };   // can't take address of an rvalue
}
