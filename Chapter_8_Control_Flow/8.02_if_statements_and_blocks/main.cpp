// 8.2 — if/else with and without braces, plus the "second statement" trap.
#include <iostream>

void unbracedTrap(int x) {
    // ── The trap ──
    // Only the *next single statement* is conditional. The second line below
    // always runs, regardless of x. The indentation is a lie.
    if (x > 0)
        std::cout << "  positive\n";
        std::cout << "  (this line ALWAYS runs)\n";
}

void braced(int x) {
    // ── The fix ──
    if (x > 0) {
        std::cout << "  positive\n";
        std::cout << "  (only when x > 0)\n";
    }
}

void elseIfChain(int x) {
    if (x < 0)       std::cout << "  negative\n";
    else if (x == 0) std::cout << "  zero\n";
    else             std::cout << "  positive\n";
}

int main() {
    std::cout << "── unbraced (x = -1) ──\n";
    unbracedTrap(-1);

    std::cout << "── braced (x = -1) ──\n";
    braced(-1);

    std::cout << "── else-if chain ──\n";
    for (int x : { -2, 0, 5 }) {
        std::cout << "x = " << x << ':';
        elseIfChain(x);
    }
}
