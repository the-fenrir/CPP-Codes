// 21.10 — operator() makes objects callable. Two uses: multi-arg indexing, stateful callables.
#include <cassert>
#include <cstddef>
#include <iostream>

// Use 1: m(row, col) — pre-C++23, operator[] only took one argument.
class Matrix2x2 {
    double m_d[2][2]{};
public:
    double&       operator()(std::size_t r, std::size_t c)       { assert(r<2 && c<2); return m_d[r][c]; }
    const double& operator()(std::size_t r, std::size_t c) const { assert(r<2 && c<2); return m_d[r][c]; }
};

// Use 2: a functor that carries state across calls.
class Counter {
    int m_count{ 0 };
public:
    int operator()() { return ++m_count; }   // not const — mutates state
};

int main() {
    Matrix2x2 m;
    m(0, 0) = 1.0; m(0, 1) = 2.0;
    m(1, 0) = 3.0; m(1, 1) = 4.0;
    std::cout << m(1, 0) << ' ' << m(1, 1) << '\n';

    Counter tick;
    std::cout << tick() << ' ' << tick() << ' ' << tick() << '\n';   // 1 2 3
}
