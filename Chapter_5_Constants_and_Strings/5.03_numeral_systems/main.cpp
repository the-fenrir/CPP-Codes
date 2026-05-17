// 5.3 — numeral systems: prefixes, sticky manipulators, binary I/O via bitset.
#include <bitset>
#include <iostream>

int main() {
    // Same value, four spellings.
    const int dec_v { 255 };
    const int oct_v { 0377 };           // leading 0 → octal
    const int hex_v { 0xFF };           // 0x / 0X  → hex
    const int bin_v { 0b1111'1111 };    // 0b / 0B  → binary (C++14)

    std::cout << "all equal? "
              << std::boolalpha
              << (dec_v == oct_v && oct_v == hex_v && hex_v == bin_v)
              << '\n';

    // Sticky output manipulators. After std::hex, ints stay hex until reset.
    std::cout << "255 in dec = " << std::dec << 255 << '\n';
    std::cout << "255 in hex = " << std::hex << 255 << '\n';
    std::cout << "255 in oct = " << std::oct << 255 << '\n';
    std::cout << std::dec;   // reset, otherwise the next int below would be octal

    // No std::bin manipulator. Use std::bitset<N>(value) for binary.
    std::cout << "255 in bin = " << std::bitset<8>{ 255 } << '\n';

    // The leading-zero trap:
    const int zip_padded { 010 };       // octal! value is 8, not 10.
    std::cout << "010 prints as " << zip_padded << '\n';
}
