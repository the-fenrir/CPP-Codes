// 24.6 — Derived classes can add new members on top of the base.
#include <iostream>
#include <string>

class Animal {
public:
    std::string m_name{};
    explicit Animal(std::string name) : m_name{ std::move(name) } {}

    void speak() const { std::cout << m_name << " makes a sound.\n"; }
};

class Dog : public Animal {
public:
    explicit Dog(std::string name) : Animal{ std::move(name) } {}

    // New behavior that Animal doesn't have.
    void fetch() const { std::cout << m_name << " fetches the stick.\n"; }
};

int main() {
    Dog rex{ "Rex" };
    rex.speak();   // inherited
    rex.fetch();   // derived-only

    Animal& a = rex;
    a.speak();
    // a.fetch();  // ERROR: Animal has no fetch(); derived-only members aren't visible
    //              through a base reference.
}
