// 8.1 — the four buckets of control flow, all in one program.
#include <iostream>

// A jump (return) inside this function changes which line runs next in main().
int classify(int n) {
    if (n < 0)  return -1;   // conditional branch + jump
    if (n == 0) return 0;
    return 1;
}

int main() {
    // ── Straight-line baseline ──
    std::cout << "start\n";

    // ── Conditional branch ──
    int x{ 7 };
    if (x % 2 == 0) std::cout << "even\n";
    else            std::cout << "odd\n";

    // ── Loop ──
    for (int i{ 0 }; i < 3; ++i)
        std::cout << "tick " << i << '\n';

    // ── Jump (function call + return) ──
    std::cout << "classify(-3) = " << classify(-3) << '\n';
    std::cout << "classify( 0) = " << classify(0)  << '\n';
    std::cout << "classify( 5) = " << classify(5)  << '\n';

    // ── (Halts shown in 8.12; not used here so main returns normally.) ──
    std::cout << "end\n";
}
