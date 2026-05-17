// 4.3 — sizeof, every fundamental type, plus a static_assert sanity check.
#include <iostream>

int main() {
    std::cout << "bool        : " << sizeof(bool)        << " byte(s)\n";
    std::cout << "char        : " << sizeof(char)        << " byte(s)\n";
    std::cout << "short       : " << sizeof(short)       << " byte(s)\n";
    std::cout << "int         : " << sizeof(int)         << " byte(s)\n";
    std::cout << "long        : " << sizeof(long)        << " byte(s)\n";
    std::cout << "long long   : " << sizeof(long long)   << " byte(s)\n";
    std::cout << "float       : " << sizeof(float)       << " byte(s)\n";
    std::cout << "double      : " << sizeof(double)      << " byte(s)\n";
    std::cout << "long double : " << sizeof(long double) << " byte(s)\n";

    // sizeof works on expressions too — no parens required there.
    int x{ 0 };
    std::cout << "sizeof x    : " << sizeof x << " byte(s)\n";

    // Pin an assumption at compile time. If you ever build for a platform where
    // int is 2 bytes, this fails the build instead of misbehaving at runtime.
    static_assert(sizeof(char) == 1, "char must be 1 byte");
    static_assert(sizeof(int)  >= 2, "int must be at least 2 bytes per the standard");
}
