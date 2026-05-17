// 5.2 — literals: suffixes, char vs. multichar, string-literal type,
//       digit separators.
#include <iostream>
#include <typeinfo>

int main() {
    // Integer literal suffixes.
    auto i  = 42;        // int
    auto u  = 42u;       // unsigned int
    auto ll = 42ll;      // long long
    std::cout << "sizeof(42)   = " << sizeof(i)  << '\n';
    std::cout << "sizeof(42u)  = " << sizeof(u)  << '\n';
    std::cout << "sizeof(42ll) = " << sizeof(ll) << '\n';

    // Floating-point literal suffixes.
    auto d = 3.14;       // double  (no suffix)
    auto f = 3.14f;      // float
    std::cout << "sizeof(3.14)  = " << sizeof(d) << '\n';
    std::cout << "sizeof(3.14f) = " << sizeof(f) << '\n';

    // Digit separators (C++14). Pure readability, no semantic effect.
    const int oneMillion{ 1'000'000 };
    std::cout << "one million = " << oneMillion << '\n';

    // Integer division vs. float division — driven by literal types.
    std::cout << "5 / 2     = " << (5 / 2)     << '\n';   // 2
    std::cout << "5.0 / 2   = " << (5.0 / 2)   << '\n';   // 2.5

    // Char vs. string literal.
    std::cout << "'a' as int  = " << static_cast<int>('a') << '\n';   // 97
    std::cout << "\"a\" length = " << sizeof("a") << " (incl. '\\0')\n"; // 2

    // The "multichar literal" footgun. Uncomment to watch your compiler warn:
    // std::cout << '.\n';   // multi-character constant — implementation-defined
    // std::cout << ".\n";      // correct: string literal containing '.' and '\n'
}
