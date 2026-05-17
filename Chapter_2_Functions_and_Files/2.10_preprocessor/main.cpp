// 2.10 — preprocessor: #define, #ifdef, and why constexpr is usually better.
#include <iostream>

#define PI_MACRO 3.14159            // text substitution; no type, no scope
constexpr double pi_constexpr{ 3.14159 };

#define VERBOSE                     // toggle — comment out to disable

int main() {
    std::cout << "PI_MACRO     = " << PI_MACRO << '\n';
    std::cout << "pi_constexpr = " << pi_constexpr << '\n';

#ifdef VERBOSE
    std::cout << "[verbose mode on]\n";
#endif

    // Classic macro footgun:
#define BAD 1 + 2
    std::cout << "BAD * 3 = " << BAD * 3 << "  (expands to 1 + 2 * 3 = 7)\n";
}
