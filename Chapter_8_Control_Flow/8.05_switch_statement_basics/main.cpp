// 8.5 — switch on an int, then on an enum class.
#include <iostream>
#include <string_view>

void grade(int score) {
    // Plain int switch: each case ends with `break`. `default` catches the rest.
    switch (score / 10) {
        case 10:
        case 9:  std::cout << "A\n"; break;     // 90-100
        case 8:  std::cout << "B\n"; break;
        case 7:  std::cout << "C\n"; break;
        case 6:  std::cout << "D\n"; break;
        default: std::cout << "F\n"; break;
    }
}

enum class Color { red, green, blue };

// Exhaustive enum switch — no `default`. Compilers (-Wswitch) warn if you add
// a new enumerator and forget to handle it here. That's the actual point.
std::string_view name(Color c) {
    switch (c) {
        case Color::red:   return "red";
        case Color::green: return "green";
        case Color::blue:  return "blue";
    }
    return "?"; // unreachable; satisfies "all paths return"
}

int main() {
    for (int s : { 100, 87, 72, 65, 40 }) {
        std::cout << s << " → ";
        grade(s);
    }

    for (Color c : { Color::red, Color::green, Color::blue })
        std::cout << name(c) << '\n';
}
