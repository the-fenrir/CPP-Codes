// 12.1 — fundamental vs. compound types: same value, three names.
#include <iostream>

int main() {
    int        x   { 42 };  // fundamental type: int
    int&       ref { x  };  // compound type:    reference to int (alias for x)
    int*       ptr { &x };  // compound type:    pointer to int (holds x's address)

    std::cout << "x   = " << x   << '\n';
    std::cout << "ref = " << ref << "  (same object as x)\n";
    std::cout << "*ptr= " << *ptr << "  (dereferenced pointer)\n";

    // Mutating through any of the three changes the same underlying object:
    ref = 100;
    std::cout << "after ref = 100 → x = " << x << '\n';

    *ptr = 7;
    std::cout << "after *ptr = 7 → x = " << x << '\n';
}
