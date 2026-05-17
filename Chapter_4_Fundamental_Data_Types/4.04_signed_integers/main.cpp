// 4.4 — signed integer ranges, integer division, and a controlled look at overflow.
#include <climits>
#include <iostream>

int main() {
    std::cout << "── ranges (this platform) ──\n";
    std::cout << "short     : " << SHRT_MIN  << " .. " << SHRT_MAX  << '\n';
    std::cout << "int       : " << INT_MIN   << " .. " << INT_MAX   << '\n';
    std::cout << "long      : " << LONG_MIN  << " .. " << LONG_MAX  << '\n';
    std::cout << "long long : " << LLONG_MIN << " .. " << LLONG_MAX << '\n';

    std::cout << "\n── integer division truncates toward zero ──\n";
    std::cout << "  8 / 5 = " <<  8 / 5  << "  (not 1.6)\n";
    std::cout << " -8 / 5 = " << -8 / 5  << "  (not -2)\n";
    std::cout << "  8 / 5.0 = " << 8 / 5.0 << "  (mixed → double division)\n";

    // ── Signed overflow is undefined behavior. ──
    // We only *talk* about it — actually computing INT_MAX + 1 here is UB and
    // would let the compiler legally produce any output (including the "right"
    // answer). Reading the values is fine.
    std::cout << "\n── overflow is UB ──\n";
    std::cout << "INT_MAX     = " << INT_MAX << '\n';
    std::cout << "INT_MAX + 1 would be undefined behavior — don't rely on any value.\n";

    // To get well-defined wrap, you have to do it through *unsigned* arithmetic:
    unsigned int u{ static_cast<unsigned int>(INT_MAX) };
    ++u;
    std::cout << "(via unsigned) INT_MAX + 1 wraps to " << u << '\n';
}
