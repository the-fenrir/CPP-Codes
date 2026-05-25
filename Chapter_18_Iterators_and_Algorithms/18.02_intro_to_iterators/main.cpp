// 18.2 — iterators: the four-operation interface that powers every algorithm.
#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{ 1, 2, 3, 4, 5 };

    // ── Manual iterator walk ────────────────────────────────────
    std::cout << "manual:   ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << ' ';      // *it dereferences, ++it advances
    }
    std::cout << '\n';

    // ── Range-based for: same loop, less syntax ─────────────────
    std::cout << "range-for:";
    for (int x : v) std::cout << ' ' << x;
    std::cout << '\n';

    // ── const_iterator: read-only view ──────────────────────────
    std::cout << "cbegin:   ";
    for (auto it = v.cbegin(); it != v.cend(); ++it) {
        // *it = 0;  // would not compile — const_iterator forbids write
        std::cout << *it << ' ';
    }
    std::cout << '\n';

    // ── Half-open range demo ────────────────────────────────────
    // end() is one past the last element. Dereferencing it is UB.
    std::cout << "size via iterators: "
              << (v.end() - v.begin()) << '\n';   // works for random-access iterators

    // ── Iterator invalidation (commented to keep the program defined) ──
    // auto it = v.begin();
    // v.push_back(6);   // may reallocate -> `it` now dangles
    // std::cout << *it; // UB if reallocation happened
}
