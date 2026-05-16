// 14.2 — the ONE language difference between struct and class.
#include <iostream>

struct PointS { int x; int y; };    // members default to PUBLIC

class PointC {
    int x{ 1 };
    int y{ 2 };
public:
    void show() const { std::cout << "from inside PointC: " << x << ',' << y << '\n'; }
};

int main() {
    PointS s{ 1, 2 };
    std::cout << "from outside PointS: " << s.x << ',' << s.y << '\n';  // OK — public by default

    PointC c;
    // std::cout << c.x;   // ← uncomment: ERROR. private by default.
    c.show();              // OK — the class accesses its own privates.
}
