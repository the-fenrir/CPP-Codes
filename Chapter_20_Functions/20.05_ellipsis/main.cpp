// 20.5 — ellipsis: the C-style variadic mechanism, and two modern replacements.
#include <cstdarg>
#include <initializer_list>
#include <iostream>
#include <numeric>

// ── C-style variadic: caller and callee must agree on count + type ──────
double findAverage(int count, ...) {
    double sum = 0.0;
    va_list list;
    va_start(list, count);                        // anchor at the last *named* param
    for (int i = 0; i < count; ++i)
        sum += va_arg(list, int);                 // type chosen by the caller, by convention
    va_end(list);                                 // mandatory
    return count > 0 ? sum / count : 0.0;
}

// ── Modern replacement #1: homogeneous list, type-checked, count known ──
double avgList(std::initializer_list<int> xs) {
    if (xs.size() == 0) return 0.0;
    return static_cast<double>(std::accumulate(xs.begin(), xs.end(), 0)) / xs.size();
}

// ── Modern replacement #2: heterogeneous, fully type-safe, compile-time count ──
template <class... Ts>
double avgTmpl(Ts... xs) {
    static_assert(sizeof...(xs) > 0, "need at least one value");
    return (static_cast<double>(xs) + ...) / sizeof...(xs);   // C++17 fold expression
}

int main() {
    std::cout << "findAverage(3, 1,2,3)   = " << findAverage(3, 1, 2, 3)   << '\n';
    std::cout << "avgList({1,2,3})        = " << avgList({1, 2, 3})        << '\n';
    std::cout << "avgTmpl(1, 2.0, 3)      = " << avgTmpl(1, 2.0, 3)        << '\n';
}
