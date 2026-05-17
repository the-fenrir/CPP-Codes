// 6.7 — relational operators and floating-point comparisons.
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

// Absolute epsilon: cheap, but scale-blind.
bool approxAbs(double a, double b, double eps = 1e-9) {
    return std::abs(a - b) < eps;
}

// Relative epsilon (Knuth): scales with magnitude, brittle near zero.
bool approxRel(double a, double b, double relEps = 1e-8) {
    const double diff = std::abs(a - b);
    return diff <= std::max(std::abs(a), std::abs(b)) * relEps;
}

// Hybrid: cover both ends.
bool approxEqual(double a, double b,
                 double absEps = 1e-12,
                 double relEps = 1e-8) {
    const double diff = std::abs(a - b);
    if (diff <= absEps) return true;
    return diff <= std::max(std::abs(a), std::abs(b)) * relEps;
}

int main() {
    std::cout << std::setprecision(17);

    double x = 0.1 + 0.2;
    double y = 0.3;
    std::cout << "0.1 + 0.2 = " << x << '\n';
    std::cout << "0.3       = " << y << '\n';
    std::cout << "x == y?     " << std::boolalpha << (x == y) << '\n';
    std::cout << "approxAbs?  " << approxAbs(x, y) << '\n';
    std::cout << "approxRel?  " << approxRel(x, y) << '\n';
    std::cout << "approxEqual?" << approxEqual(x, y) << '\n';

    // ── NaN comparisons ─────────────────────────────────────────
    double nan = std::numeric_limits<double>::quiet_NaN();
    std::cout << "\nnan == nan? " << (nan == nan) << "   // false; NaN never equals anything\n";
    std::cout << "nan != nan? " << (nan != nan) << "   // true; this is the classic NaN test\n";

    // ── bool comparisons: don't overcompare ─────────────────────
    bool ok{ true };
    if (ok)               std::cout << "use `if (ok)`, not `if (ok == true)`\n";
    if (!ok)              std::cout << "(won't print)\n";
}
