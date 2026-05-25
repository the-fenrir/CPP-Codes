// 17.2 — three ways to ask the length, three ways to index.
#include <array>
#include <iostream>
#include <iterator>  // std::size, std::ssize

int main() {
    constexpr std::array a { 10, 20, 30, 40, 50 };

    // ── length ─────────────────────────────────────────────────
    std::cout << "a.size()      = " << a.size() << '\n';        // size_t
    std::cout << "std::size(a)  = " << std::size(a) << '\n';    // size_t
    std::cout << "std::ssize(a) = " << std::ssize(a) << '\n';   // signed (C++20)

    // ── indexing ───────────────────────────────────────────────
    std::cout << "a[0]          = " << a[0] << '\n';            // unchecked
    std::cout << "a.at(1)       = " << a.at(1) << '\n';         // throws on OOB
    std::cout << "std::get<2>(a)= " << std::get<2>(a) << '\n';  // compile-time checked

    // Loop with the matching unsigned type to avoid sign-compare warnings.
    std::cout << "all:";
    for (std::size_t i { 0 }; i < a.size(); ++i)
        std::cout << ' ' << a[i];
    std::cout << '\n';

    // std::get<> is a compile-time check; the line below would be a
    // *compile error*, not a runtime exception:
    // std::get<99>(a);

    static_assert(std::get<4>(a) == 50);
}
