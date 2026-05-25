// 17.3 — passing std::array (fixed size, templated), and returning by value.
#include <array>
#include <iostream>

// Fixed size — only accepts std::array<int, 5>.
void printFixed(const std::array<int, 5>& a) {
    for (int x : a) std::cout << x << ' ';
    std::cout << '\n';
}

// Any size, any element type — one template, many instantiations.
template <typename T, std::size_t N>
void printAny(const std::array<T, N>& a) {
    for (const T& x : a) std::cout << x << ' ';
    std::cout << '\n';
}

// Returning by value is free thanks to mandatory copy elision (C++17).
std::array<int, 4> makeSquares() {
    return { 1, 4, 9, 16 };
}

int main() {
    std::array<int, 5> a { 1, 2, 3, 4, 5 };
    std::array<double, 3> b { 1.5, 2.5, 3.5 };

    printFixed(a);        // ok — exact match
    // printFixed(b);     // would not compile: different size & element type

    printAny(a);          // T=int,    N=5
    printAny(b);          // T=double, N=3

    auto squares { makeSquares() };  // no copy (prvalue, mandatory elision)
    printAny(squares);
}
