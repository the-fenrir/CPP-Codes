// 16.7 — three legitimate ways to write a reverse loop over a vector.
#include <iostream>
#include <vector>

int main() {
    std::vector v{ 'a', 'b', 'c', 'd', 'e' };

    // 1. std::ssize (C++20) — signed size, the cleanest signed-loop idiom.
    std::cout << "ssize:        ";
    for (auto i{ std::ssize(v) - 1 }; i >= 0; --i)
        std::cout << v[static_cast<std::size_t>(i)] << ' ';
    std::cout << '\n';

    // 2. Cast-once-at-boundary — verbose but explicit.
    std::cout << "int boundary: ";
    const int n{ static_cast<int>(v.size()) };
    for (int i{ n - 1 }; i >= 0; --i)
        std::cout << v[static_cast<std::size_t>(i)] << ' ';
    std::cout << '\n';

    // 3. size_t with care: stop *after* using 0 by checking before the decrement.
    std::cout << "size_t guard: ";
    if (!v.empty()) {
        for (std::size_t i{ v.size() }; i-- > 0; )  // post-decrement after compare
            std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}
