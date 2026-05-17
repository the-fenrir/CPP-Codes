// 10.6 — static_cast: the safe, named, everyday cast.
#include <iostream>

int main() {
    // 1) Fix integer-division by casting ONE operand before dividing.
    int a = 7, b = 2;
    std::cout << "a / b           = " <<                       a / b           << "  (int)\n";
    std::cout << "double(a) / b   = " << static_cast<double>(a) / b            << "  (FP)\n";
    std::cout << "double(a / b)   = " << static_cast<double>(a / b)            << "  (still 3 — divided first!)\n";

    // 2) Print a char as a number.
    char c = 'A';
    std::cout << "c          = " << c                               << '\n';  // 'A'
    std::cout << "int(c)     = " << static_cast<int>(c)             << '\n';  // 65

    // 3) Deliberate narrowing inside brace init — cast tells the compiler "I mean it."
    double d = 3.9;
    int    n{ static_cast<int>(d) };   // would be ill-formed without the cast
    std::cout << "int from 3.9 (truncated): " << n << '\n';

    // 4) Casts truncate, they don't round.
    std::cout << "static_cast<int>( 3.9) = " << static_cast<int>( 3.9) << '\n';
    std::cout << "static_cast<int>(-3.9) = " << static_cast<int>(-3.9) << '\n';
}
