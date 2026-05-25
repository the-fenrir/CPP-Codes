// 25.11 — non-member operator<< forwards to a virtual member print().
#include <iostream>
#include <ostream>
#include <vector>

class Shape {
public:
    virtual std::ostream& print(std::ostream& out) const = 0;
    virtual ~Shape() = default;
};

// ONE non-member operator<< for the whole hierarchy. Dispatch happens inside print().
std::ostream& operator<<(std::ostream& out, const Shape& s) {
    return s.print(out);
}

class Circle : public Shape {
    int m_radius;
public:
    Circle(int r) : m_radius{ r } {}
    std::ostream& print(std::ostream& out) const override {
        return out << "Circle(r=" << m_radius << ")";
    }
};

class Square : public Shape {
    int m_side;
public:
    Square(int s) : m_side{ s } {}
    std::ostream& print(std::ostream& out) const override {
        return out << "Square(s=" << m_side << ")";
    }
};

int main() {
    Circle c{ 5 };
    Square s{ 3 };

    // Direct: virtual dispatch picks the right print().
    std::cout << c << '\n';
    std::cout << s << '\n';

    // Polymorphic container — same machinery handles both.
    std::vector<const Shape*> shapes{ &c, &s };
    for (const auto* p : shapes)
        std::cout << " - " << *p << '\n';

    // Chaining works because print() returns the stream.
    std::cout << "both: " << c << " and " << s << '\n';
}
