// 15.2 — caller: only #includes the header.
#include "point.h"
#include <iostream>

int main() {
    Point p{ 3, 4 };
    p.print();
    std::cout << "x=" << p.x() << " y=" << p.y() << '\n';
}
