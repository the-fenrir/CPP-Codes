// 12.9 — the four const+pointer combinations, read right-to-left.
#include <iostream>

int main() {
    int x { 5 };
    int y { 99 };

    // (1) Pointer to non-const: can modify, can repoint.
    int* a { &x };
    *a = 10;
    a  = &y;
    std::cout << "(1) int*           — x = " << x << ", *a = " << *a << '\n';

    // (2) Pointer to const: cannot modify pointee, can repoint.
    const int* b { &x };
    // *b = 20;            // ERROR: pointee is const through b
    b = &y;                // OK: repoint
    std::cout << "(2) const int*     — *b = " << *b << '\n';

    // (3) Const pointer to non-const: can modify, cannot repoint.
    int* const c { &x };
    *c = 30;
    // c = &y;             // ERROR: c is const (pointer)
    std::cout << "(3) int* const     — x  = " << x << '\n';

    // (4) Const pointer to const: neither.
    const int* const d { &x };
    // *d = 40;            // ERROR
    // d  = &y;            // ERROR
    std::cout << "(4) const int* const — *d = " << *d << '\n';

    // A const pointer to a non-const object — the object can still change
    // by other names:
    int z { 0 };
    const int* e { &z };
    z = 42;                 // legal: modify z directly
    std::cout << "non-const z via const int* e: *e = " << *e << '\n';

    // Mnemonic: read right-to-left.
    //   int *       const  → "const pointer to int"
    //   const int * const  → "const pointer to const int"
}
