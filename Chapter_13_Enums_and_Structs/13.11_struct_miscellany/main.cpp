// 13.11 — Nested structs, arrays in structs, and padding/alignment.
#include <array>
#include <iostream>
#include <string>

struct Employee {
    int         id;
    std::string name;
};

struct Company {
    std::string         name;
    Employee            ceo;
    std::array<int, 3>  topSalaries;  // structs can hold arrays
};

// Two structs, same members, different declaration order → potentially different size.
struct Loose  { char c1; int i; char c2; };   // padding around c1 *and* c2
struct Packed { int  i;  char c1; char c2; }; // padding only at the end

int main() {
    Company c{
        "Acme",
        { 99, "Eve" },
        { 250000, 180000, 175000 }
    };

    std::cout << c.name << " — CEO " << c.ceo.name << '\n';
    std::cout << "top salary: " << c.topSalaries[0] << '\n';

    std::cout << "\nsizeof(Loose)  = " << sizeof(Loose)  << '\n';
    std::cout << "sizeof(Packed) = " << sizeof(Packed) << '\n';
    // On a typical 64-bit system: Loose = 12, Packed = 8.
}
