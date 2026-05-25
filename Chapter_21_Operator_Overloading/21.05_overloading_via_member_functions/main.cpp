// 21.5 — canonical pattern: `+=` as a member, then `+` as a non-member that uses `+=`.
#include <iostream>

class Cents {
    int m_cents{};
public:
    explicit Cents(int c) : m_cents{ c } {}
    int value() const { return m_cents; }

    // Member: mutates *this, returns ref to self for chaining `a += b += c`.
    Cents& operator+=(const Cents& rhs) {
        m_cents += rhs.m_cents;
        return *this;
    }
};

// Non-member: build a fresh value out of a copy + the member +=.
// Left arg taken by value lets us mutate it and return it; common copy-and-modify idiom.
Cents operator+(Cents lhs, const Cents& rhs) {
    lhs += rhs;
    return lhs;
}

int main() {
    Cents a{ 5 };
    Cents b{ 3 };
    Cents sum = a + b;
    std::cout << "5 + 3 = " << sum.value() << '\n';

    a += b;
    std::cout << "a after a += b: " << a.value() << '\n';
}
