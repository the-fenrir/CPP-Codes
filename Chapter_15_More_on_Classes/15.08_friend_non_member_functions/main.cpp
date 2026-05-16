// 15.8 — friend non-member: classic operator<< overload.
#include <iostream>

class Money {
    int m_cents;
public:
    explicit Money(int cents) : m_cents{ cents } {}

    // Grant operator<< access to private m_cents.
    friend std::ostream& operator<<(std::ostream& os, const Money& m);
};

std::ostream& operator<<(std::ostream& os, const Money& m) {
    os << '$' << (m.m_cents / 100) << '.';
    int c = m.m_cents % 100;
    if (c < 10) os << '0';
    return os << c;
}

int main() {
    Money a{ 4250 };
    Money b{    7 };
    std::cout << "a = " << a << ", b = " << b << '\n';
}
