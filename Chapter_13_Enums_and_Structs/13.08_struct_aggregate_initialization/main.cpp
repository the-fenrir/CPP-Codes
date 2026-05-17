// 13.8 — Aggregate initialization, every variant.
#include <iostream>
#include <string>

struct Employee {
    int         id;
    std::string name;
    double      salary;
};

void print(const Employee& e) {
    std::cout << '#' << e.id << ' ' << '"' << e.name << '"' << " $" << e.salary << '\n';
}

int main() {
    Employee a{ 1, "Alice", 50000.0 };  // positional, all members
    Employee c{};                       // empty: all value-initialized
    Employee d{ .id = 4, .name = "Dan", .salary = 75000.0 };  // C++20 designated
    Employee e{ .id = 5, .salary = 90000.0 };                 // skip a designated member (silent)

    // Employee bad{ 6, "Z", 1.5f };    // OK (float→double widens)
    // Employee narrow{ 7, "X", 5 };    // OK
    // int      narrowing{ 3.5 };       // compile error — narrowing in braces

    for (const auto& emp : { a, c, d, e }) print(emp);
}
