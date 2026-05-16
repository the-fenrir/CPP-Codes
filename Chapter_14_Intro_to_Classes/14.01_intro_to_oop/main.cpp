// 14.1 — same task in procedural vs. object-oriented style.
#include <iostream>
#include <string>

// ── Procedural ───────────────────────────────────────────────
struct EmployeeP { std::string name; int id; double salary; };
void printEmployee(const EmployeeP& e) {
    std::cout << e.name << " (#" << e.id << ") $" << e.salary << '\n';
}

// ── Object-oriented ──────────────────────────────────────────
struct EmployeeOO {
    std::string name;
    int id;
    double salary;

    void print() const {
        std::cout << name << " (#" << id << ") $" << salary << '\n';
    }
};

int main() {
    EmployeeP  p{ "Alice", 1, 50000 };
    EmployeeOO o{ "Bob",   2, 60000 };

    printEmployee(p);  // procedural: behavior lives outside the data
    o.print();         // OO: behavior travels with the data
}
