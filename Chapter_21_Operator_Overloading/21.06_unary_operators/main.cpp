// 21.6 — unary `-` returns a fresh negated value; `!` returns bool.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }
    Cents operator-() const { return Cents{ -m_cents }; }
};

class Point {
    double m_x{}, m_y{}, m_z{};
public:
    Point() = default;
    Point(double x, double y, double z) : m_x{ x }, m_y{ y }, m_z{ z } {}

    Point operator-() const { return Point{ -m_x, -m_y, -m_z }; }
    bool  operator!() const { return m_x == 0 && m_y == 0 && m_z == 0; }

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
    }
};

int main() {
    Cents c{ 7 };
    std::cout << (-c).value() << '\n';   // -7

    Point a{ 1.0, -2.0, 3.0 };
    Point z{};
    std::cout << -a << '\n';             // Point(-1, 2, -3)
    std::cout << "a is origin? " << std::boolalpha << !a << '\n';   // false
    std::cout << "z is origin? " << !z << '\n';                     // true
}
