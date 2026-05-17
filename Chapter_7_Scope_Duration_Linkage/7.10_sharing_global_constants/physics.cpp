// 7.10 — one consumer of the shared constants.
#include "constants.h"
#include <iostream>

void describe_circle(double radius) {
    const double area = Constants::pi * radius * radius;
    std::cout << "  area of r=" << radius << " circle: " << area << '\n';
}
