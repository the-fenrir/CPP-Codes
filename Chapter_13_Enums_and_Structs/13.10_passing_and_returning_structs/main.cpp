// 13.10 — Passing and returning structs.
// The `Fraction` struct here is the same one Chapter 14's quiz converts to a class.
#include <iostream>
#include <sstream>

struct Fraction {
    int numerator{ 0 };
    int denominator{ 1 };
};

// Read-only input → pass by const reference.
void printFraction(const Fraction& f) {
    std::cout << f.numerator << '/' << f.denominator << '\n';
}

// Returns a new struct. By value, not by reference — the result is a local.
// C++17 mandatory copy elision makes this free.
Fraction multiply(const Fraction& a, const Fraction& b) {
    return Fraction{ a.numerator * b.numerator,
                     a.denominator * b.denominator };
}

// Read user input into a Fraction. Wrapped over a stringstream here so the
// program is self-contained / non-interactive.
Fraction getFraction(std::istream& in) {
    Fraction f;
    in >> f.numerator >> f.denominator;
    return f;
}

int main() {
    std::istringstream in{ "2 5  3 8" };

    Fraction f1{ getFraction(in) };
    Fraction f2{ getFraction(in) };

    printFraction(f1);
    printFraction(f2);

    Fraction product{ multiply(f1, f2) };
    std::cout << "f1 * f2 = ";
    printFraction(product);
}
