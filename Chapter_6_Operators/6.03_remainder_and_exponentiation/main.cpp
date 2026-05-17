// 6.3 — remainder and exponentiation pitfalls.
#include <cmath>
#include <cstdint>
#include <iostream>

// Integer exponentiation by squaring. Caller is responsible for overflow.
constexpr std::int64_t intPow(std::int64_t base, int exp) {
    std::int64_t result{ 1 };
    while (exp > 0) {
        if (exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

int main() {
    // ── % follows the sign of the dividend ──────────────────────
    std::cout << " 5 %  2 = " <<  5 %  2 << '\n';   //  1
    std::cout << "-5 %  2 = " << -5 %  2 << '\n';   // -1
    std::cout << " 5 % -2 = " <<  5 % -2 << '\n';   //  1
    std::cout << "-5 % -2 = " << -5 % -2 << '\n';   // -1

    // ── the "is x odd?" trap ────────────────────────────────────
    int n = -5;
    std::cout << "-5 % 2 == 1 ? " << ((n % 2) == 1 ? "yes" : "no")
              << "   // wrong way: misses negative odds\n";
    std::cout << "-5 % 2 != 0 ? " << ((n % 2) != 0 ? "yes" : "no")
              << "   // right way\n";

    // ── ^ is XOR, not exponent ─────────────────────────────────
    // (Variables here just to suppress clang's helpful "did you mean xor?"
    //  warning on a literal ^ literal — we want the warning to teach, but
    //  not to break -Wall.)
    int two{ 2 }, three{ 3 };
    std::cout << "2 ^ 3 (bitwise XOR) = " << (two ^ three) << "   // 1, not 8\n";

    // ── std::pow returns double, can lose precision ────────────
    std::cout << "std::pow(10, 3)     = " << std::pow(10, 3) << '\n';
    std::cout << "intPow(10, 18)      = " << intPow(10, 18)  << "  // exact integer\n";
    std::cout << "std::pow(10, 18)    = " << static_cast<long long>(std::pow(10, 18))
              << "  // may differ by a few\n";
}
