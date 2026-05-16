// 14.3 — member functions inline and out-of-line, plus overloading.
#include <iostream>

class Date {
public:
    int year, month, day;

    void print() const {  // inline definition
        std::cout << year << '-' << month << '-' << day << '\n';
    }

    void setDate(int y, int m, int d);  // declaration only
    void setDate(int isoLikeYYYYMMDD);  // overload
};

// Out-of-line definitions — use Class::name.
void Date::setDate(int y, int m, int d) {
    year = y; month = m; day = d;
}
void Date::setDate(int yyyymmdd) {
    year  = yyyymmdd / 10000;
    month = (yyyymmdd / 100) % 100;
    day   = yyyymmdd % 100;
}

int main() {
    Date d{};
    d.setDate(2025, 1, 15);
    d.print();
    d.setDate(20260516);    // overload by signature
    d.print();
}
