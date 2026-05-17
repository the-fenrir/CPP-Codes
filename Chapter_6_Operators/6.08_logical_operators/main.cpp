// 6.8 — logical operators: short-circuit, precedence, De Morgan.
#include <iostream>

bool reportAndReturn(const char* label, bool value) {
    std::cout << "    [evaluated " << label << "]\n";
    return value;
}

int main() {
    std::boolalpha(std::cout);

    // ── short-circuit on && ─────────────────────────────────────
    std::cout << "false && X:\n";
    bool r1 = reportAndReturn("L=false", false) && reportAndReturn("R", true);
    std::cout << "  result: " << r1 << "   // R never evaluated\n";

    // ── short-circuit on || ─────────────────────────────────────
    std::cout << "true || X:\n";
    bool r2 = reportAndReturn("L=true", true) || reportAndReturn("R", false);
    std::cout << "  result: " << r2 << "   // R never evaluated\n";

    // ── short-circuit as a *guard* (don't deref a null pointer) ─
    int* p = nullptr;
    if (p && *p > 0) {
        std::cout << "won't reach this\n";
    } else {
        std::cout << "guard worked — *p never accessed when p is null\n";
    }

    // ── precedence trap: !x > y ─────────────────────────────────
    // The compiler is right to warn here — the bug is the whole point.
    // Suppress the warning locally so the chapter still builds clean.
    int x{ 0 }, y{ -1 };
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wlogical-not-parentheses"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wlogical-not-parentheses"
#endif
    std::cout << "!x > y    = " << (!x > y)    << "   // means (!x) > y → 1 > -1 → true\n";
#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif
    std::cout << "!(x > y)  = " << (!(x > y))  << "   // probably what you meant\n";

    // ── XOR via != for bools ────────────────────────────────────
    bool a{ true }, b{ false };
    std::cout << "a XOR b   = " << (a != b) << '\n';

    // ── De Morgan ───────────────────────────────────────────────
    bool L{ true }, R{ false };
    std::cout << "!(L && R) = " << !(L && R) << "   ==   !L || !R = " << (!L || !R) << '\n';
    std::cout << "!(L || R) = " << !(L || R) << "   ==   !L && !R = " << (!L && !R) << '\n';
}
