// 14.13 — temporaries: created, used, destroyed in one expression.
#include <iostream>

class Point {
    int m_x, m_y;
public:
    Point(int x, int y) : m_x{ x }, m_y{ y } {
        std::cout << "  ctor   (" << m_x << ',' << m_y << ")\n";
    }
    ~Point() {
        std::cout << "  ~dtor  (" << m_x << ',' << m_y << ")\n";
    }
    void print() const { std::cout << '(' << m_x << ',' << m_y << ")\n"; }
};

void take(const Point& p) { p.print(); }

int main() {
    std::cout << "1) temporary as method receiver:\n";
    Point{ 1, 2 }.print();   // born, used, dies at the `;`

    std::cout << "2) temporary as argument:\n";
    take(Point{ 3, 4 });     // born, bound to const&, dies at the `;`

    std::cout << "3) const& extends lifetime:\n";
    const Point& kept = Point{ 5, 6 };
    kept.print();
    std::cout << "(still alive)\n";
    // kept (and its temporary) dies at end of main.
}
