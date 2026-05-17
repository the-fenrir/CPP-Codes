// 13.3 — Conversions between unscoped enums and integers.
#include <cstdint>
#include <iostream>
#include <sstream>

enum Color { red, green, blue };

// Fixed underlying type: lets us forward-declare, and bounds the storage.
enum Pet : std::int8_t {
    cat,
    dog,
    pig,
    whale,
};

int main() {
    Color c{ blue };
    std::cout << "blue prints as int: " << c << '\n';      // implicit enum→int

    // int → enum requires a cast (or list-init from a literal in C++17+).
    int input{ 1 };
    Color c2{ static_cast<Color>(input) };
    std::cout << "static_cast<Color>(1) = " << c2 << '\n'; // 1 (green)

    // Reading an enum from a stream: read an int, then cast.
    std::istringstream in{ "2" };
    int raw{};
    in >> raw;
    Color c3{ static_cast<Color>(raw) };
    std::cout << "read from stream:    " << c3 << '\n';    // 2 (blue)

    // Fixed-base enums work the same way.
    Pet p{ dog };
    std::cout << "Pet dog as int:       " << static_cast<int>(p) << '\n';
}
