// 24.5 — Access specifiers and inheritance.
//   Show which base members a derived class can and cannot touch.
#include <iostream>

class Base {
public:
    int m_pub{ 1 };
protected:
    int m_prot{ 2 };
private:
    int m_priv{ 3 };
public:
    int peek_priv() const { return m_priv; }  // bridge for demo purposes
};

class Derived : public Base {
public:
    void show() const {
        std::cout << "pub  = " << m_pub  << '\n';   // OK: public stays public
        std::cout << "prot = " << m_prot << '\n';   // OK: protected visible to derived
        // std::cout << "priv = " << m_priv << '\n'; // ERROR: private is inaccessible
        std::cout << "priv (via base accessor) = " << peek_priv() << '\n';
    }
};

int main() {
    Derived d;
    d.show();

    std::cout << "from outside: pub=" << d.m_pub << '\n';
    // std::cout << d.m_prot << '\n';  // ERROR: protected is not callable from outside
    // std::cout << d.m_priv << '\n';  // ERROR: private is not callable from outside
}
