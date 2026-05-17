// 8.3 — Common if-statement bugs, each shown wrong then right.
#include <iostream>

void danglingElse(int a, int b) {
    // ── Without braces, `else` binds to the NEAREST unmatched `if` ──
    if (a > 0)
        if (b > 0) std::cout << "  both positive\n";
        else       std::cout << "  a>0, b<=0 (this `else` belongs to inner if)\n";

    // ── With braces, the intent is explicit ──
    if (a > 0) {
        if (b > 0) std::cout << "  both positive (braced)\n";
    } else {
        std::cout << "  a<=0 (braced — `else` clearly outer)\n";
    }
}

void chainedComparison(int x) {
    // ── WRONG: parses as (0 < x) < 10  →  bool < 10  →  always true ──
    if (0 < x < 10)
        std::cout << "  chained: 'in range' (this fires even for x=999)\n";

    // ── RIGHT ──
    if (0 < x && x < 10)
        std::cout << "  &&-chained: actually in range\n";
}

void rangeCheck(int x) {
    // Demonstrate the chained comparison bug at x=999.
    chainedComparison(x);
}

int main() {
    std::cout << "── Dangling else, a=3 b=-1 ──\n";
    danglingElse(3, -1);

    std::cout << "── Chained comparison, x = 5 ──\n";
    rangeCheck(5);
    std::cout << "── Chained comparison, x = 999 ──\n";
    rangeCheck(999);
}
