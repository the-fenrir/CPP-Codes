// 7.1 — blocks introduce scope; names die at the closing brace.
#include <iostream>

int main() {
    int outer{ 1 };
    std::cout << "outer in function body = " << outer << '\n';

    {                          // ── nested block: new scope ──
        int inner{ 2 };
        std::cout << "inner in nested block = " << inner << '\n';
        std::cout << "outer still visible  = " << outer << '\n';
    }                          // `inner` ends here
    // std::cout << inner;     // ERROR: inner is out of scope

    // The classic missing-block bug. Only the first statement is the
    // `if` body; the second statement runs unconditionally.
    int n{ 5 };
    if (n < 0)
        std::cout << "negative, flipping sign\n";
        n = -n;                // <-- runs regardless of `n < 0`
    std::cout << "n = " << n << "  (expected 5; got " << n << ")\n";

    // Fixed version with an explicit block:
    int m{ 5 };
    if (m < 0) {
        std::cout << "negative, flipping sign\n";
        m = -m;
    }
    std::cout << "m = " << m << "  (expected 5)\n";
}
