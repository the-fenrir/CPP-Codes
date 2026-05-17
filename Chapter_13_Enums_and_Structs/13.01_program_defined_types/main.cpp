// 13.1 — A first look at program-defined types: an enum and a struct.
// Both are previews; the rest of the chapter unpacks them.
#include <iostream>
#include <string>

// A program-defined type: a fixed set of named integer constants.
enum Color { red, green, blue };

// A program-defined type: a named record of values.
struct Point {
    double x;
    double y;
};

int main() {
    Color  c{ green };
    Point  p{ 3.0, 4.0 };

    std::cout << "Color c  = " << c << '\n';     // prints 1 — enum→int conversion (13.3)
    std::cout << "Point p  = (" << p.x << ", " << p.y << ")\n";

    // The type system now distinguishes Color from Point — you can't
    // accidentally pass one where the other is expected. That's the win.
}
