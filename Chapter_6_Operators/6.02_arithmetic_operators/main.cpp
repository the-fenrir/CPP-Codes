// 6.2 — arithmetic operators: integer vs. floating-point division, casts, by-zero.
#include <iostream>

int main() {
    int a{ 7 }, b{ 4 };

    // ── integer division: truncates toward zero ─────────────────
    std::cout << "7 / 4 (int)            = " << a / b << "    // 1, fractional part dropped\n";
    std::cout << "-7 / 4 (int)           = " << -a / b << "   // -1, NOT -2 (truncation toward 0)\n";

    // ── floating-point division ─────────────────────────────────
    std::cout << "7.0 / 4                = " << 7.0 / 4 << "  // 1.75 (one float makes it float)\n";

    // ── force float division on int variables ───────────────────
    std::cout << "static_cast<double>(a)/b = " << static_cast<double>(a) / b << '\n';

    // ── compound assignment ─────────────────────────────────────
    int x{ 10 };
    x += 5;     // x = x + 5
    x *= 2;     // x = x * 2
    std::cout << "(10 += 5) *= 2         = " << x << "   // 30\n";

    // ── floating-point divide by zero ───────────────────────────
    // IEEE 754 systems produce inf / nan rather than trapping.
    double inf  = 1.0 / 0.0;
    double nan  = 0.0 / 0.0;
    std::cout << "1.0 / 0.0              = " << inf << '\n';
    std::cout << "0.0 / 0.0              = " << nan << '\n';

    // Integer division by zero would be undefined behavior — we don't run it.
}
