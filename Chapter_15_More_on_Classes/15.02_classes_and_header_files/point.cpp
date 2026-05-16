// 15.2 — source: out-of-line definitions live here.
#include "point.h"
#include <iostream>

Point::Point(int x, int y) : m_x{ x }, m_y{ y } {}

void Point::print() const {
    std::cout << '(' << m_x << ',' << m_y << ")\n";
}
