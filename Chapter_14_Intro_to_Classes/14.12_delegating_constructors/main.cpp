// 14.12 — delegating constructors: one implementation, many entry points.
#include <iostream>

class Rectangle {
    int m_w, m_h;
public:
    // "Real" constructor — does the work.
    Rectangle(int w, int h) : m_w{ w }, m_h{ h } {
        std::cout << "made " << m_w << 'x' << m_h << '\n';
    }
    // Square — delegate to the real one.
    Rectangle(int side) : Rectangle{ side, side } {}
    // Default — same trick.
    Rectangle()         : Rectangle{ 1, 1 }       {}

    int area() const { return m_w * m_h; }
};

int main() {
    Rectangle a;            // → Rectangle(1,1)
    Rectangle b{ 5 };       // → Rectangle(5,5)
    Rectangle c{ 3, 4 };    // → Rectangle(3,4)
    std::cout << "areas: " << a.area() << ' ' << b.area() << ' ' << c.area() << '\n';
}
