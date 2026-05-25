// Chapter 18 quiz solutions.
//   Q1: selection sort rewritten with iterators (function template)
//   Q2: std::find_if + erase-remove idiom
//   Q3: discussion — see NOTES.md
//   Q4: timing std::sort vs std::stable_sort
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

// ── Q1: iterator-based selection sort ───────────────────────────────
//
// Design notes:
//  • Generic over the iterator type, so the same template sorts vectors,
//    arrays, raw pointer ranges, etc.
//  • std::min_element returns an iterator; std::iter_swap swaps the values
//    two iterators point to — cleaner than writing `std::swap(*a, *b)`.
//  • Compare iterators with !=, never <. Plenty of iterator categories
//    don't support ordering; != works for all of them.
template <typename It>
void selectionSort(It first, It last) {
    for (auto i = first; i != last; ++i) {
        auto smallest = std::min_element(i, last);
        std::iter_swap(i, smallest);
    }
}

// ── Q4 helper: reusable Timer (same as 18.4) ────────────────────────
class Timer {
    using clock = std::chrono::steady_clock;
    std::chrono::time_point<clock> m_start{ clock::now() };
public:
    void reset() { m_start = clock::now(); }
    double elapsed() const {
        return std::chrono::duration<double>{ clock::now() - m_start }.count();
    }
};

int main() {
    // ── Q1 ──────────────────────────────────────────────────────
    std::cout << "── Q1: iterator-based selection sort ──\n";
    std::vector<int> v1{ 5, 1, 4, 2, 8, 3 };
    selectionSort(v1.begin(), v1.end());
    std::cout << "sorted:";
    for (int x : v1) std::cout << ' ' << x;
    std::cout << '\n';

    // ── Q2 ──────────────────────────────────────────────────────
    std::cout << "\n── Q2: find_if + erase-remove ──\n";
    std::vector<int> v2{ 3, -2, 7, -4, 8, 1, 6 };

    // (a) first negative
    auto neg = std::find_if(v2.begin(), v2.end(),
                            [](int x){ return x < 0; });
    if (neg != v2.end()) std::cout << "first negative: " << *neg << '\n';
    else                 std::cout << "first negative: none\n";

    // (b) drop every even. erase-remove idiom: std::remove_if shuffles the
    //     "kept" elements to the front and returns the new logical end;
    //     erase() then trims the tail off. (C++20 also has std::erase_if.)
    v2.erase(std::remove_if(v2.begin(), v2.end(),
                            [](int x){ return x % 2 == 0; }),
             v2.end());
    std::cout << "survivors:";
    for (int x : v2) std::cout << ' ' << x;
    std::cout << '\n';

    // ── Q4: time std::sort vs std::stable_sort ──────────────────
    std::cout << "\n── Q4: std::sort vs std::stable_sort ──\n";
    constexpr int N = 50'000;
    std::vector<int> base(N);
    for (int i = 0; i < N; ++i) base[i] = i;
    std::mt19937 rng{ 42 };                       // fixed seed -> reproducible
    std::shuffle(base.begin(), base.end(), rng);

    std::vector<int> a = base;
    Timer t;
    std::sort(a.begin(), a.end());
    const double sort_ = t.elapsed();

    std::vector<int> b = base;
    t.reset();
    std::stable_sort(b.begin(), b.end());
    const double stable = t.elapsed();

    std::cout << "std::sort        (N=" << N << "): " << sort_  << " s\n";
    std::cout << "std::stable_sort (N=" << N << "): " << stable << " s\n";
    if (sort_ > 0.0) {
        std::cout << "stable / sort = " << (stable / sort_) << "x\n";
    }
    // Sanity check: both produce the same sorted sequence.
    std::cout << "results agree: " << std::boolalpha << (a == b) << '\n';
}
