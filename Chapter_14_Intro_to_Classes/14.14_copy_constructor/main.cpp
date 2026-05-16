// 14.14 — copy constructor: explicit, default, and =delete.
#include <iostream>

class Point {
    int m_x, m_y;
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}

    // Explicit copy constructor — same as the implicit one, but we can trace it.
    Point(const Point& other) : m_x{ other.m_x }, m_y{ other.m_y } {
        std::cout << "  [copy " << m_x << ',' << m_y << "]\n";
    }

    void print() const { std::cout << m_x << ',' << m_y << '\n'; }
};

class NonCopyable {
    int m_value;
public:
    NonCopyable(int v) : m_value{ v } {}
    NonCopyable(const NonCopyable&) = delete;   // copying is forbidden
    int value() const { return m_value; }
};

void byValue(Point p) { p.print(); }  // triggers a copy on call

int main() {
    Point a{ 1, 2 };
    Point b{ a };           // copy ctor
    Point c = a;            // also copy ctor (NOT operator=)
    byValue(a);             // copy ctor on the parameter

    NonCopyable n{ 42 };
    std::cout << "nc=" << n.value() << '\n';
    // NonCopyable m{ n };   // ← uncomment: ERROR. copy is deleted.
}
