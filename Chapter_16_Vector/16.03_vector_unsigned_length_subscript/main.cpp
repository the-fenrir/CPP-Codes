// 16.3 — unsigned size_t vs. signed loop counters, .at() bounds checking.
#include <exception>
#include <iostream>
#include <vector>

int main() {
    std::vector v{ 10, 20, 30, 40, 50 };

    // Style 1: size_t everywhere. Clean for forward loops.
    std::cout << "forward (size_t): ";
    for (std::size_t i{ 0 }; i < v.size(); ++i)
        std::cout << v[i] << ' ';
    std::cout << '\n';

    // Style 2: std::ssize (C++20) returns a signed size. Safer for reverse loops.
    std::cout << "reverse (ssize): ";
    for (auto i{ std::ssize(v) - 1 }; i >= 0; --i)
        std::cout << v[static_cast<std::size_t>(i)] << ' ';
    std::cout << '\n';

    // Style 3: cast once at the loop boundary, then use int internally.
    std::cout << "int + cast:      ";
    const int n{ static_cast<int>(v.size()) };
    for (int i{ 0 }; i < n; ++i)
        std::cout << v[static_cast<std::size_t>(i)] << ' ';
    std::cout << '\n';

    // .at() throws on out-of-range. Useful while debugging.
    try {
        std::cout << "v.at(99) = ";
        std::cout << v.at(99) << '\n';
    } catch (const std::exception& e) {
        std::cout << "(caught) " << e.what() << '\n';
    }

    // The unsigned underflow trap: this would loop forever.
    //   for (std::size_t i = v.size() - 1; i >= 0; --i) ...  // i >= 0 is always true
}
