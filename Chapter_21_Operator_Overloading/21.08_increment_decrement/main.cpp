// 21.8 — prefix returns ref to modified self; postfix returns old value by value.
#include <iostream>

class Digit {
    int m_d{ 0 };  // 0..9
public:
    explicit Digit(int d = 0) : m_d{ d } {}
    int value() const { return m_d; }

    // Prefix: ++d
    Digit& operator++() {
        m_d = (m_d == 9) ? 0 : m_d + 1;
        return *this;
    }
    // Postfix: d++ — `int` parameter is a dummy that picks this overload.
    Digit operator++(int) {
        Digit old{ *this };
        ++(*this);          // delegate to prefix
        return old;
    }

    Digit& operator--() {
        m_d = (m_d == 0) ? 9 : m_d - 1;
        return *this;
    }
    Digit operator--(int) {
        Digit old{ *this };
        --(*this);
        return old;
    }
};

int main() {
    Digit d{ 8 };
    std::cout << "start:    " << d.value() << '\n';
    std::cout << "++d -> "    << (++d).value() << ", d=" << d.value() << '\n';   // 9, d=9
    std::cout << "d++ -> "    << (d++).value() << ", d=" << d.value() << '\n';   // 9, d=0 (wrap)
    std::cout << "--d -> "    << (--d).value() << ", d=" << d.value() << '\n';   // 9 (wrap), d=9
    std::cout << "d-- -> "    << (d--).value() << ", d=" << d.value() << '\n';   // 9, d=8
}
