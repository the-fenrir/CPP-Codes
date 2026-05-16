// 15.6 — inline static member: one shared variable across all instances.
#include <iostream>

class Widget {
    inline static int s_nextId{ 1 };   // C++17: define + init in the class body
    int m_id;
public:
    Widget() : m_id{ s_nextId++ } {}    // each instance grabs the next id

    int  id() const { return m_id; }
    static int nextId() { return s_nextId; }  // static accessor — see 15.7
};

int main() {
    Widget a, b, c;
    std::cout << "ids: " << a.id() << ' ' << b.id() << ' ' << c.id() << '\n';
    std::cout << "next id will be: " << Widget::nextId() << '\n';
}
