// 14.2 — a first class: Date with a print() member.
#include <iostream>

class Date {
public:               // without this, the members below would be private (the class default).
    int year;
    int month;
    int day;

    void print() const {
        std::cout << year << '-' << month << '-' << day << '\n';
    }
};

int main() {
    Date d{ 2025, 1, 15 };  // aggregate-style init works here because all members are public.
    d.print();
}
