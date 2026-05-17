// 8.8 — while: count up, "may run zero times", and an exit-mid-iteration loop.
#include <iostream>

int main() {
    // ── Counting up ──
    int i{ 0 };
    while (i < 5) {
        std::cout << i << ' ';
        ++i;
    }
    std::cout << '\n';

    // ── May run zero times: condition checked BEFORE first iteration ──
    int n{ 0 };
    while (n > 0) {
        std::cout << "never prints\n";
        --n;
    }
    std::cout << "(loop body skipped because 0 > 0 was false)\n";

    // ── Exit-mid-iteration ──
    //   The "natural" exit isn't a precondition — it's "we just discovered we're done."
    //   while (true) + break expresses that cleanly without contorting the condition.
    int sum{ 0 };
    int x{ 1 };
    while (true) {
        sum += x;
        if (sum > 20) break;
        ++x;
    }
    std::cout << "sum reached " << sum << " at x=" << x << '\n';
}
