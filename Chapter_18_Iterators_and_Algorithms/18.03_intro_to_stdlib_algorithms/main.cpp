// 18.3 — a small tour of <algorithm>: find, find_if, count_if, sort, for_each.
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> v{ 4, 1, 5, 9, 2, 6, 5, 3, 5 };

    // ── std::find: locate a value ───────────────────────────────
    if (auto it = std::find(v.begin(), v.end(), 9); it != v.end()) {
        std::cout << "found 9 at index " << (it - v.begin()) << '\n';
    }

    // ── std::find_if: locate by predicate (lambda) ──────────────
    auto is_even = [](int x) { return x % 2 == 0; };
    if (auto it = std::find_if(v.begin(), v.end(), is_even); it != v.end()) {
        std::cout << "first even = " << *it << '\n';
    }

    // ── std::count_if: tally elements matching a predicate ──────
    const auto fives = std::count_if(v.begin(), v.end(),
                                     [](int x){ return x == 5; });
    std::cout << "count of 5s = " << fives << '\n';

    // ── std::sort with a custom comparator ──────────────────────
    std::vector<int> w = v;
    std::sort(w.begin(), w.end(), std::greater<>{});      // descending
    std::cout << "desc:   ";
    for (int x : w) std::cout << ' ' << x;
    std::cout << '\n';

    // ── std::for_each: apply a callable to each element ─────────
    int sum = 0;
    std::for_each(v.begin(), v.end(), [&](int x){ sum += x; });
    std::cout << "sum = " << sum << '\n';

    // ── C++20 ranges: drop the begin/end boilerplate ────────────
    std::vector<int> r = v;
    std::ranges::sort(r);                                  // ascending
    std::cout << "asc:    ";
    for (int x : r) std::cout << ' ' << x;
    std::cout << '\n';
}
