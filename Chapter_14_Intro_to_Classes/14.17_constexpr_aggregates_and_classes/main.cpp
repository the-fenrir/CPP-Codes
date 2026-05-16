// 14.17 — constexpr classes: compile-time objects with member functions.
#include <iostream>

class Point {
    int m_x, m_y;
public:
    constexpr Point(int x, int y) : m_x{ x }, m_y{ y } {}
    constexpr int x() const { return m_x; }
    constexpr int y() const { return m_y; }
    constexpr int sumSq() const { return m_x*m_x + m_y*m_y; }
};

// Aggregate-style (no user ctor) — also usable in constant expressions.
struct Color { int r, g, b; };

int main() {
    constexpr Point  p{ 3, 4 };
    constexpr Color  red{ 255, 0, 0 };

    static_assert(p.sumSq() == 25, "compile-time math should be exact");
    static_assert(red.r == 255);

    std::cout << "p=(" << p.x() << ',' << p.y() << ") sumSq=" << p.sumSq() << '\n';
    std::cout << "red=" << red.r << ',' << red.g << ',' << red.b << '\n';
}
