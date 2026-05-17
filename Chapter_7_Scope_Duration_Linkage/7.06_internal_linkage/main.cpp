// 7.6 — caller proves a.cpp's s_count and b.cpp's s_count are independent.
#include "internal.h"
#include <iostream>

int main() {
    bump_in_a(); bump_in_a(); bump_in_a();   // a's s_count: 0 → 3
    bump_in_b();                              // b's s_count: 0 → 10

    std::cout << "a::s_count = " << read_in_a() << "  (expected 3)\n";
    std::cout << "b::s_count = " << read_in_b() << "  (expected 10)\n";
    std::cout << "they're separate variables that share a name.\n";
}
