// 14.16 — converting constructors and `explicit`.
#include <iostream>

class Dollars {
    int m_cents;
public:
    Dollars(int cents) : m_cents{ cents } {}   // converting ctor — implicit allowed
    int cents() const { return m_cents; }
};

class StrictDollars {
    int m_cents;
public:
    explicit StrictDollars(int cents) : m_cents{ cents } {}  // implicit forbidden
    int cents() const { return m_cents; }
};

void print(Dollars d)       { std::cout << "Dollars cents=" << d.cents() << '\n'; }
void printS(StrictDollars d) { std::cout << "StrictDollars cents=" << d.cents() << '\n'; }

int main() {
    print(500);                       // OK: implicit int → Dollars
    // printS(500);                   // ← uncomment: ERROR. explicit blocks implicit conversion.
    printS(StrictDollars{ 500 });     // OK: explicit construction
    printS(static_cast<StrictDollars>(500));  // also OK
}
