// 13.7 — Structs: data members and the member-selection operator.
#include <iostream>
#include <string>

struct Employee {
    int         id;
    std::string name;
    double      salary;
};

struct Company {
    std::string name;
    Employee    ceo;     // composition: a struct holding a struct
};

int main() {
    Employee a{ 1, "Alice", 50000.0 };
    Employee b{ 2, "Bob",   60000.0 };

    a.salary = 55000.0;  // mutate one member; b is unaffected

    std::cout << a.name << " #" << a.id << " $" << a.salary << '\n';
    std::cout << b.name << " #" << b.id << " $" << b.salary << '\n';

    Company c{ "Acme", { 99, "Eve", 250000.0 } };
    std::cout << c.name << " CEO: " << c.ceo.name
              << " ($" << c.ceo.salary << ")\n";
}
