// 6.5 — comma operator: precedence trap and for-loop idiom.
#include <iostream>

// Per-statement warning suppression: the two unused-value warnings below are
// the *point* of the demonstration — the comma operator's result is being
// discarded. We silence them locally so the chapter builds clean.
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wunused-value"
#elif defined(__GNUC__)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wunused-value"
#endif

int main() {
    int a{ 1 }, b{ 2 };

    // ── the precedence trap ─────────────────────────────────────
    int z;
    z = a, b;       // parses as (z = a), b;  → z gets 1, b is discarded
    std::cout << "z = a, b;       → z = " << z << "   // expected 2? got 1\n";

    // ── with explicit parens ────────────────────────────────────
    z = (a, b);     // comma operator: evaluate a, then b; result is b
    std::cout << "z = (a, b);     → z = " << z << "   // 2 as the operator promises\n";

    // ── idiomatic: in a for header ──────────────────────────────
    std::cout << "two-cursor loop: ";
    for (int i = 0, j = 5; i < j; ++i, --j) {
        std::cout << '(' << i << ',' << j << ") ";
    }
    std::cout << '\n';

    // ── separator vs. operator ──────────────────────────────────
    int p, q{ 7 };  // commas here are SEPARATORS, not the operator
    p = 3;
    std::cout << "p=" << p << " q=" << q << "   // declaration commas != operator\n";
}

#if defined(__clang__)
#  pragma clang diagnostic pop
#elif defined(__GNUC__)
#  pragma GCC diagnostic pop
#endif
