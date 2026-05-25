// 17.1 — three ways to spell std::array, and [] vs at().
#include <array>
#include <iostream>
#include <stdexcept>

int main() {
    // Fully spelled out — type and size as template args.
    std::array<int, 5> a { 10, 20, 30, 40, 50 };

    // C++17 CTAD — compiler deduces std::array<int, 3>.
    std::array b { 1, 2, 3 };

    // constexpr — the whole array is a compile-time value.
    constexpr std::array<int, 4> primes { 2, 3, 5, 7 };
    static_assert(primes[2] == 5);  // checked at compile time

    std::cout << "a[0] = " << a[0] << '\n';      // unchecked, fast
    std::cout << "b.at(1) = " << b.at(1) << '\n';// bounds-checked, throws on OOB

    // .at() throws on out-of-range; demonstrate the catch.
    try {
        std::cout << a.at(99) << '\n';
    } catch (const std::out_of_range& e) {
        std::cout << "caught: " << e.what() << '\n';
    }
}
