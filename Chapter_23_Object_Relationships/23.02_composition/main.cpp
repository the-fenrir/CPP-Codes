// 23.2 — Composition. Creature contains a Point2D by value:
//   - born with the Creature
//   - destroyed with the Creature
//   - never shared with another Creature
//   - doesn't know Creature exists.
#include <iostream>
#include <string>

class Point2D {
    int m_x{};
    int m_y{};
public:
    Point2D() { std::cout << "  Point2D() default\n"; }
    Point2D(int x, int y) : m_x{ x }, m_y{ y } {
        std::cout << "  Point2D(" << x << ',' << y << ")\n";
    }
    ~Point2D() { std::cout << "  ~Point2D(" << m_x << ',' << m_y << ")\n"; }

    void moveTo(int x, int y) { m_x = x; m_y = y; }
    friend std::ostream& operator<<(std::ostream& o, const Point2D& p) {
        return o << '(' << p.m_x << ',' << p.m_y << ')';
    }
};

class Creature {
    std::string m_name;
    Point2D     m_location;   // ← part. Lifetime bound to *this.
public:
    Creature(std::string name, const Point2D& loc)
        : m_name{ std::move(name) }, m_location{ loc }
    {
        std::cout << "Creature(" << m_name << ")\n";
    }
    ~Creature() { std::cout << "~Creature(" << m_name << ")\n"; }

    void moveTo(int x, int y) { m_location.moveTo(x, y); }
    friend std::ostream& operator<<(std::ostream& o, const Creature& c) {
        return o << c.m_name << " @ " << c.m_location;
    }
};

int main() {
    {
        Creature c{ "Goblin", Point2D{ 1, 1 } };
        std::cout << c << '\n';
        c.moveTo(5, 7);
        std::cout << c << '\n';
    }   // ← ~Creature, then ~Point2D — reverse declaration order
    std::cout << "(both gone)\n";
}
