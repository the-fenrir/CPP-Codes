// Chapter 14 quiz solutions.
//   Q1a + Q1b: Point2d with print() and distanceTo()
//   Q2:       Fraction class with member functions
//   Q3/Q4:    discussion — see NOTES.md
#include <cmath>
#include <iostream>
#include <numeric>

// ── Q1: Point2d ─────────────────────────────────────────────────────
//
// Design notes:
//  • Two constructors: a defaulted no-arg one and a two-arg one. There's
//    deliberately NO single-double constructor — that's what makes
//    `Point2d third{ 4.0 };` fail to compile (the spec requires this).
//  • Neither constructor is `explicit`. The two-arg constructor isn't a
//    converting constructor (it takes two args), so `explicit` adds nothing.
//    The no-arg one can't convert anyway.
//  • `print()` and `distanceTo()` are `const` — they don't mutate state and
//    callers may have a `const Point2d&`.
class Point2d {
    double m_x{ 0.0 };
    double m_y{ 0.0 };
public:
    Point2d() = default;
    Point2d(double x, double y) : m_x{ x }, m_y{ y } {}

    void print() const {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }

    double distanceTo(const Point2d& other) const {
        const double dx = m_x - other.m_x;
        const double dy = m_y - other.m_y;
        return std::sqrt(dx*dx + dy*dy);
    }
};

// ── Q2: Fraction as a class ─────────────────────────────────────────
//
// Design notes:
//  • `explicit` constructor (Q3 discussion). Without it, any int silently
//    converts to a Fraction — `multiply(5)` would mean `multiply(Fraction{5,1})`,
//    which is almost never what the caller intended.
//  • `reduce()` is private — it's an internal invariant maintainer (every
//    Fraction is stored in lowest terms with a positive denominator), not
//    something the caller should call directly. Forces the class to keep the
//    invariant for itself.
//  • `multiply()` returns a Fraction *by value*, not by reference. The result
//    is a fresh fraction whose lifetime must outlive the call site; returning
//    a reference would dangle. With C++17 mandatory copy elision, the return
//    costs nothing.
class Fraction {
    int m_numerator;
    int m_denominator;

    void reduce() {
        const int g = std::gcd(m_numerator, m_denominator);
        if (g > 1) { m_numerator /= g; m_denominator /= g; }
        if (m_denominator < 0) { m_numerator = -m_numerator; m_denominator = -m_denominator; }
    }
public:
    explicit Fraction(int num = 0, int den = 1)
        : m_numerator{ num }, m_denominator{ den }
    {
        reduce();
    }

    void print() const {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }

    Fraction multiply(const Fraction& other) const {
        return Fraction{ m_numerator * other.m_numerator,
                         m_denominator * other.m_denominator };
    }
};

int main() {
    std::cout << "── Q1: Point2d ──\n";
    Point2d a;
    Point2d b{ 3.0, 4.0 };
    a.print();
    b.print();
    std::cout << "distance(a,b) = " << a.distanceTo(b) << '\n';

    std::cout << "\n── Q2: Fraction ──\n";
    Fraction f1{ 2, 5 };
    Fraction f2{ 3, 8 };
    f1.print();
    f2.print();
    std::cout << "f1 * f2 = ";
    f1.multiply(f2).print();
}
