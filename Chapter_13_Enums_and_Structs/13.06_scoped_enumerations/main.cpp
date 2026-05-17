// 13.6 — Scoped enumerations.
#include <iostream>
#include <string_view>
#include <type_traits>

enum class Color { red, green, blue };
enum class Fruit { banana, apple, cherry };

// No implicit Color→int. Provide an operator<< when you want to print one.
constexpr std::string_view name(Color c) {
    switch (c) {
        case Color::red:   return "red";
        case Color::green: return "green";
        case Color::blue:  return "blue";
    }
    return "???";
}
std::ostream& operator<<(std::ostream& out, Color c) { return out << name(c); }

int main() {
    Color c{ Color::red };
    Fruit f{ Fruit::apple };

    // c == f                  // compile error — different types
    // std::cout << Color::red; // would be error without our operator<<; works now
    std::cout << "c = " << c << '\n';

    // Underlying integer requires an explicit cast.
    auto raw = static_cast<std::underlying_type_t<Fruit>>(f);
    std::cout << "Fruit::apple underlying = " << raw << '\n';

    // C++20: `using enum` brings the enumerators into local scope.
    {
        using enum Color;
        Color c2{ blue };       // no Color:: prefix needed inside this block
        std::cout << "local c2 = " << c2 << '\n';
    }
}
