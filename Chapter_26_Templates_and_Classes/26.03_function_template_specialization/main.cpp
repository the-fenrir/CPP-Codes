// 26.3 — function template specialization vs. plain overloads.
#include <iomanip>
#include <iostream>
#include <string>

// Primary template.
template <typename T>
void print(const T& x) {
    std::cout << x << '\n';
}

// Full specialization for double — scientific format.
template <>
void print<double>(const double& d) {
    std::cout << std::scientific << d << std::defaultfloat << '\n';
}

// Plain overload for bool — preferred alternative to specialization.
void print(bool b) {
    std::cout << (b ? "true" : "false") << '\n';
}

int main() {
    print(42);                       // primary template, T = int
    print(std::string{ "hello" });   // primary template, T = std::string
    print(3.14);                     // specialization for double
    print(true);                     // non-template overload (wins over any specialization)
    print(false);
}
