// 23.5 — Dependency. Point depends on std::ostream only inside print() /
// operator<<. No member is stored; any ostream-derived sink works.
#include <iostream>
#include <sstream>
#include <string>

class Point {
    int m_x, m_y;
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {}

    // operator<< depends on std::ostream for this single call. After it
    // returns, Point has no knowledge of `out` whatsoever.
    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << '(' << p.m_x << ',' << p.m_y << ')';
    }
};

int main() {
    Point p{ 3, 4 };

    std::cout << "to cout:  " << p << '\n';        // depends on std::cout

    std::ostringstream oss;                         // a different ostream sink
    oss << "to oss: " << p;
    std::cout << oss.str() << '\n';                 // Point neither knows nor cares
}
