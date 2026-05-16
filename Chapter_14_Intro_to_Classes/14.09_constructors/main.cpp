// 14.9 — constructors run on object creation.
#include <iostream>

class Date {
    int m_year{}, m_month{}, m_day{};
public:
    Date(int y, int m, int d) {       // parameterized constructor (body-assignment style)
        m_year = y; m_month = m; m_day = d;
        std::cout << "constructed Date " << y << '-' << m << '-' << d << '\n';
    }

    void print() const {
        std::cout << m_year << '-' << m_month << '-' << m_day << '\n';
    }
};

int main() {
    Date d1{ 2025, 1, 15 };   // brace init — preferred
    Date d2( 2026, 5, 16 );   // direct init — also fine
    d1.print();
    d2.print();
    // Date d3;               // ← ERROR: no default constructor exists once we declared a custom one.
}
