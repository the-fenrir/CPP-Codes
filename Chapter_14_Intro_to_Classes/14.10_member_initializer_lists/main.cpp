// 14.10 — member initializer lists: the right way to set member values.
#include <iostream>

class Date {
    int m_year;
    int m_month;
    int m_day;
    const int m_epoch;   // const members MUST be in the init list — can't be assigned later.
public:
    Date(int y, int m, int d)
        : m_year{ y }, m_month{ m }, m_day{ d }, m_epoch{ 1970 }
    {
        // Body runs after init list — members are already set.
    }

    void print() const {
        std::cout << m_year << '-' << m_month << '-' << m_day
                  << " (epoch=" << m_epoch << ")\n";
    }
};

int main() {
    Date d{ 2025, 1, 15 };
    d.print();
}
