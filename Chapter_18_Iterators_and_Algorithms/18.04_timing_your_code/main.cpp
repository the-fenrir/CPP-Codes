// 18.4 — a reusable Timer and a head-to-head: hand selection sort vs std::sort.
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

// Reusable RAII-ish timer. Construct -> starts. Call elapsed() any time.
class Timer {
    using clock = std::chrono::steady_clock;
    std::chrono::time_point<clock> m_start{ clock::now() };
public:
    void reset() { m_start = clock::now(); }
    double elapsed() const {                       // seconds, as double
        return std::chrono::duration<double>{ clock::now() - m_start }.count();
    }
};

static void selectionSort(std::vector<int>& a) {
    const std::size_t n = a.size();
    for (std::size_t i = 0; i + 1 < n; ++i) {
        std::size_t smallest = i;
        for (std::size_t j = i + 1; j < n; ++j) {
            if (a[j] < a[smallest]) smallest = j;
        }
        std::swap(a[i], a[smallest]);
    }
}

int main() {
    // Build a reproducible shuffled vector so both sorts see the same input.
    constexpr int N = 10'000;
    std::vector<int> base(N);
    for (int i = 0; i < N; ++i) base[i] = i;
    std::mt19937 rng{ 42 };
    std::shuffle(base.begin(), base.end(), rng);

    // ── Hand-rolled selection sort: O(n^2) ──────────────────────
    std::vector<int> a = base;
    Timer t;
    selectionSort(a);
    const double hand = t.elapsed();
    std::cout << "selection sort (N=" << N << "): " << hand << " s\n";

    // ── std::sort: O(n log n), in-place ─────────────────────────
    std::vector<int> b = base;
    t.reset();
    std::sort(b.begin(), b.end());
    const double std_ = t.elapsed();
    std::cout << "std::sort      (N=" << N << "): " << std_ << " s\n";

    // Print the ratio rather than absolute numbers (portable comparison).
    if (std_ > 0.0) {
        std::cout << "selection / std::sort = " << (hand / std_) << "x\n";
    }

    // Sanity check: both vectors should be sorted and equal.
    std::cout << "results agree: "
              << std::boolalpha << (a == b) << '\n';
}
