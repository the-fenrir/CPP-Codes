// 4.6 — fixed-width integers, the 8-bit "prints as char" gotcha, and size_t.
#include <cstddef>   // std::size_t
#include <cstdint>   // std::int8_t etc.
#include <iostream>

int main() {
    std::cout << "── exact widths ──\n";
    std::cout << "int8_t   : " << sizeof(std::int8_t)   << " byte(s)\n";
    std::cout << "int16_t  : " << sizeof(std::int16_t)  << " byte(s)\n";
    std::cout << "int32_t  : " << sizeof(std::int32_t)  << " byte(s)\n";
    std::cout << "int64_t  : " << sizeof(std::int64_t)  << " byte(s)\n";

    std::cout << "\n── the int8_t / uint8_t gotcha ──\n";
    std::uint8_t small{ 65 };
    std::cout << "uint8_t{ 65 } printed naively : " << small               << '\n'; // 'A'
    std::cout << "uint8_t{ 65 } cast to int     : " << static_cast<int>(small) << '\n'; // 65

    std::cout << "\n── size_t ──\n";
    std::size_t n{ sizeof(int) };
    std::cout << "sizeof(int)         : " << n << '\n';
    std::cout << "sizeof(std::size_t) : " << sizeof(std::size_t) << " byte(s)"
              << "  (matches the platform's address width)\n";
}
