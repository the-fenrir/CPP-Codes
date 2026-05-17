// 13.4 — Enum ↔ string conversion.
#include <iostream>
#include <string>
#include <string_view>

enum Color { red, green, blue, unknown };

// Enum → string. `string_view` over string literals: no allocation, no dangle.
constexpr std::string_view getColorName(Color c) {
    switch (c) {
        case red:     return "red";
        case green:   return "green";
        case blue:    return "blue";
        case unknown: return "unknown";
    }
    return "???";  // unreachable for in-range values; silences -Wreturn-type
}

// String → enum. Validate; fall through to a sentinel.
Color colorFromString(std::string_view s) {
    if (s == "red")   return red;
    if (s == "green") return green;
    if (s == "blue")  return blue;
    return unknown;
}

int main() {
    for (Color c : { red, green, blue, unknown }) {
        std::cout << "name(" << static_cast<int>(c) << ") = " << getColorName(c) << '\n';
    }

    std::cout << '\n';
    for (std::string_view s : { "red", "green", "purple", "blue" }) {
        Color c{ colorFromString(s) };
        std::cout << "parse(\"" << s << "\") = " << getColorName(c) << '\n';
    }
}
