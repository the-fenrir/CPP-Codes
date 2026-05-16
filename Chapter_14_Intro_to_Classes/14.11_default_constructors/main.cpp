// 14.11 — default constructors, default arguments, and =default.
#include <iostream>

class Date {
    int m_year, m_month, m_day;
public:
    // One constructor with all-default args acts as both default and parameterized ctor.
    Date(int y = 1970, int m = 1, int d = 1)
        : m_year{ y }, m_month{ m }, m_day{ d } {}

    void print() const {
        std::cout << m_year << '-' << m_month << '-' << m_day << '\n';
    }
};

class Counter {
    int m_n{ 0 };  // default member initializer
public:
    Counter() = default;       // explicitly keep the compiler-generated default ctor
    Counter(int n) : m_n{ n } {}

    int value() const { return m_n; }
};

int main() {
    Date d1{};                 // 1970-1-1
    Date d2{ 2025 };           // 2025-1-1
    Date d3{ 2026, 5, 16 };    // 2026-5-16
    d1.print(); d2.print(); d3.print();

    Counter c1{};
    Counter c2{ 42 };
    std::cout << "Counters: " << c1.value() << ", " << c2.value() << '\n';
}
