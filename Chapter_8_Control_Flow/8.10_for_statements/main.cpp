// 8.10 — counting for, while-equivalent, range-based for, infinite for(;;).
#include <iostream>
#include <vector>

int main() {
    // ── Counting for ──
    std::cout << "for: ";
    for (int i{ 0 }; i < 5; ++i)
        std::cout << i << ' ';
    std::cout << '\n';

    // ── Same loop rewritten as while — shows exactly what `for` collapses ──
    std::cout << "while: ";
    {
        int i{ 0 };                  // init
        while (i < 5) {              // condition
            std::cout << i << ' ';
            ++i;                     // step
        }
    }
    std::cout << '\n';

    // ── Range-based for: no index, no off-by-one ──
    std::vector<int> v{ 10, 20, 30 };
    std::cout << "range: ";
    for (const auto& e : v) std::cout << e << ' ';
    std::cout << '\n';

    // ── Mutating range-based for ──
    for (auto& e : v) e *= 2;
    std::cout << "doubled: ";
    for (const auto& e : v) std::cout << e << ' ';
    std::cout << '\n';

    // ── Infinite for(;;) with break — uncommon but legal ──
    int sum{ 0 };
    for (;;) {
        sum += 3;
        if (sum >= 12) break;
    }
    std::cout << "sum=" << sum << '\n';
}
