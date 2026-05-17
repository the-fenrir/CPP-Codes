// 13.9 — Default member initializers as a safety net.
#include <iostream>
#include <string>

struct Employee {
    int         id     { 0 };
    std::string name   { "unnamed" };
    double      salary { 0.0 };
};

void print(const Employee& e) {
    std::cout << '#' << e.id << ' ' << '"' << e.name << '"' << " $" << e.salary << '\n';
}

int main() {
    Employee a;                          // built-ins were a footgun; defaults fix it
    Employee b{};                        // value-init: equivalent to defaults here
    Employee c{ 7 };                     // id=7, the rest fall back to defaults
    Employee d{ 8, "Dan" };              // id, name explicit; salary defaults
    Employee e{ 9, "Eve", 90000.0 };     // all explicit

    for (const auto& emp : { a, b, c, d, e }) print(emp);
}
