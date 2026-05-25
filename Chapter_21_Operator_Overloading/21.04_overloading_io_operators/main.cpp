// 21.4 — operator<< and operator>> as friend non-members; both return the stream.
#include <iostream>
#include <sstream>

class Point {
    double m_x{}, m_y{}, m_z{};
public:
    Point() = default;
    Point(double x, double y, double z) : m_x{ x }, m_y{ y }, m_z{ z } {}

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ')';
        return out;  // chaining
    }
    friend std::istream& operator>>(std::istream& in, Point& p) {
        in >> p.m_x >> p.m_y >> p.m_z;
        // If extraction failed, the stream state already records it; nothing extra to do.
        return in;
    }
};

int main() {
    Point a{ 1.0, 2.0, 3.0 };
    std::cout << a << '\n';            // chained <<
    std::cout << a << " and " << a << '\n';

    std::istringstream src{ "5 6 7" };
    Point b;
    src >> b;
    std::cout << "parsed: " << b << '\n';
}
