// 13.5 — Overload operator<< and operator>> for a Color enum.
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

enum Color { red, green, blue, unknown };

constexpr std::string_view getColorName(Color c) {
    switch (c) {
        case red:     return "red";
        case green:   return "green";
        case blue:    return "blue";
        case unknown: return "unknown";
    }
    return "???";
}

// Free function. Returns the stream so chaining works.
std::ostream& operator<<(std::ostream& out, Color c) {
    return out << getColorName(c);
}

// Read a word; map to a Color; flag the stream on bad input.
std::istream& operator>>(std::istream& in, Color& c) {
    std::string word;
    in >> word;
    if      (word == "red")   c = red;
    else if (word == "green") c = green;
    else if (word == "blue")  c = blue;
    else { c = unknown; in.setstate(std::ios_base::failbit); }
    return in;
}

int main() {
    Color c{ green };
    std::cout << "c is " << c << '\n';        // chaining works
    std::cout << "all: " << red << ", " << green << ", " << blue << '\n';

    std::istringstream in{ "blue purple" };
    Color c1{}, c2{};
    in >> c1;
    in >> c2;   // sets failbit on "purple"

    std::cout << "parsed first:  " << c1 << '\n';
    std::cout << "parsed second: " << c2
              << "  (stream good? " << std::boolalpha << static_cast<bool>(in) << ")\n";
}
