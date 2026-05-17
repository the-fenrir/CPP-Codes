// 6.1 — precedence vs. associativity vs. order of evaluation.
#include <iostream>

int sideEffect(const char* label, int value) {
    std::cout << "  evaluated " << label << '\n';
    return value;
}

int main() {
    // ── precedence: * before + ─────────────────────────────────
    std::cout << "4 + 2 * 3        = " << (4 + 2 * 3)   << "   // (4 + (2*3)) = 10\n";
    std::cout << "(4 + 2) * 3      = " << ((4 + 2) * 3) << "   // 18, parens override\n";

    // ── associativity: subtraction is left-to-right ────────────
    std::cout << "7 - 4 - 1        = " << (7 - 4 - 1)   << "   // ((7-4)-1) = 2, NOT 7-(4-1)=4\n";

    // ── associativity: assignment is right-to-left ─────────────
    int a{}, b{}, c{ 9 };
    a = b = c;  // a = (b = c)
    std::cout << "after a=b=c=9    a=" << a << " b=" << b << " c=" << c << '\n';

    // ── order of evaluation is NOT precedence ──────────────────
    // The compiler is free to evaluate the two arguments in either
    // order. The output below is implementation-defined.
    std::cout << "f() + g() — which runs first?\n";
    int sum = sideEffect("left",  1) + sideEffect("right", 2);
    std::cout << "  sum = " << sum << "  (always 3, but order above varies)\n";
}
