// 21.2 — friend operators let you mix `Cents` with raw `int` on either side.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }

    // Three friend overloads → covers (Cents+Cents), (Cents+int), (int+Cents).
    friend Cents operator+(const Cents& a, const Cents& b) { return Cents{ a.m_cents + b.m_cents }; }
    friend Cents operator+(const Cents& a, int n)          { return Cents{ a.m_cents + n }; }
    friend Cents operator+(int n, const Cents& a)          { return Cents{ n + a.m_cents }; }
};

int main() {
    Cents c{ 4 };
    std::cout << (c + Cents{ 2 }).value() << '\n';  // 6
    std::cout << (c + 2).value()          << '\n';  // 6
    std::cout << (2 + c).value()          << '\n';  // 6  — only works because operator+ is non-member
}
