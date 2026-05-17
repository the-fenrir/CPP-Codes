// 3.5 — conditional-compilation debug prints.
//
// Build silent (default):
//   make 3.05
// Build verbose:
//   CXXFLAGS="-std=c++20 -Wall -Wextra -Wpedantic -O0 -g -DENABLE_DEBUG" make 3.05
//
// The DBG(x) calls cost zero at runtime when ENABLE_DEBUG is undefined — the
// preprocessor erases them entirely.
#include <iostream>
#include <vector>

#ifdef ENABLE_DEBUG
    #define DBG(x) do { std::cerr << "[DBG] " << x << '\n'; } while (0)
#else
    #define DBG(x) do {} while (0)
#endif

int countEven(const std::vector<int>& v) {
    DBG("entering countEven, size=" << v.size());
    int count{ 0 };
    for (std::size_t i{ 0 }; i < v.size(); ++i) {
        DBG("i=" << i << " v[i]=" << v[i]);
        if (v[i] % 2 == 0) {
            ++count;
            DBG("  even, count=" << count);
        }
    }
    DBG("returning " << count);
    return count;
}

int main() {
    std::vector<int> v{ 2, 4, 6, 7, 8 };
    std::cout << "count = " << countEven(v) << "  (expect 4)\n";

#ifdef ENABLE_DEBUG
    std::cerr << "[DBG] build: ENABLE_DEBUG is ON\n";
#else
    // Silent in this build. Rerun with -DENABLE_DEBUG to see the trace.
#endif
}
