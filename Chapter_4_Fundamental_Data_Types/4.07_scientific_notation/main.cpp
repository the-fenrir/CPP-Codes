// 4.7 — scientific notation as C++ literals.
#include <iostream>

int main() {
    // Four spellings of the same value.
    double a{ 0.0000016 };
    double b{ 1.6e-6 };       // normalized scientific
    double c{ 16e-7 };        // same value, not normalized
    double d{ 0.16e-5 };      // same value, also not normalized

    std::cout << "0.0000016 = " << a << '\n';
    std::cout << "1.6e-6    = " << b << '\n';
    std::cout << "16e-7     = " << c << '\n';
    std::cout << "0.16e-5   = " << d << '\n';

    // Big number, small number.
    double avogadro{ 6.022e23 };   // ~6.022 × 10^23
    double electron { 1.602e-19 }; // electron charge in coulombs
    std::cout << "Avogadro  = " << avogadro << '\n';
    std::cout << "electron  = " << electron << '\n';

    // Literal type is double — narrowing to int is rejected by brace-init.
    // int x{ 2e3 };  // error: narrowing conversion
    int x{ static_cast<int>(2e3) };  // explicit cast is fine: 2000
    std::cout << "2e3 as int = " << x << '\n';
}
