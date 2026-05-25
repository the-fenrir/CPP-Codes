// 21.3 — when the public interface is enough, skip `friend`. Plain free function.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }
};

// No `friend`. Only uses Cents::value() — the same API external callers use.
Cents operator-(const Cents& a, const Cents& b) {
    return Cents{ a.value() - b.value() };
}

int main() {
    Cents c1{ 10 };
    Cents c2{ 3 };
    std::cout << (c1 - c2).value() << " cents\n";  // 7 cents
}
