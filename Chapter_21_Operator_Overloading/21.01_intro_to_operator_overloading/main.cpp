// 21.1 — operator overloading is just function overloading with a funny name.
// `c1 + c2` is sugar for a call to a function named `operator+`.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }
};

// Free-function overload. `a + b` ⇒ `operator+(a, b)`.
// This version uses only the public interface — no `friend` needed.
Cents operator+(const Cents& a, const Cents& b) {
    return Cents{ a.value() + b.value() };
}

int main() {
    Cents c1{ 6 };
    Cents c2{ 8 };
    Cents sum = c1 + c2;   // identical to operator+(c1, c2)

    std::cout << "6 + 8 = " << sum.value() << " cents\n";
}
