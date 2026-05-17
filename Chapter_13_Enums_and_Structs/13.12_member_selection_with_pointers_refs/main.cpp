// 13.12 — Member access through value, reference, and pointer.
#include <iostream>
#include <string>

struct Employee {
    int         id;
    std::string name;
};

struct Company {
    std::string name;
    Employee    ceo;
};

int main() {
    Company c{ "Acme", { 99, "Eve" } };

    // value: dot.
    std::cout << c.name << " / " << c.ceo.name << '\n';

    // reference: dot, same as the value.
    Company& r{ c };
    std::cout << r.name << " / " << r.ceo.name << '\n';

    // pointer: arrow at the first hop.
    Company* p{ &c };
    std::cout << p->name << " / " << p->ceo.name << '\n';   // p->ceo is by value
    std::cout << "(*p).name = " << (*p).name << '\n';        // long form

    // Pointer to a member that is itself a struct: arrow then dot.
    Employee* pe{ &c.ceo };
    std::cout << "pe->name = " << pe->name << '\n';
}
