// 7.10 — second consumer; same constants, no ODR clash thanks to `inline`.
#include "constants.h"
#include <iostream>

void describe_circle(double radius);   // declared in physics.cpp

int main() {
    std::cout << "pi = " << Constants::pi << '\n';
    std::cout << "e  = " << Constants::e  << '\n';
    std::cout << "max class size = " << Constants::g_max_class_size << '\n';

    describe_circle(1.0);
    describe_circle(2.5);

    // Compile-time usable thanks to constexpr.
    static_assert(Constants::g_max_class_size == 35);
}
