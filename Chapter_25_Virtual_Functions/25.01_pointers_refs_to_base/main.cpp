// 25.1 — A Base& bound to a Derived still calls Base's non-virtual members.
#include <iostream>
#include <string_view>

class Animal {
protected:
    std::string m_name;
    Animal(std::string_view name) : m_name{ name } {}
public:
    const std::string& getName() const { return m_name; }
    std::string_view speak() const { return "???"; } // non-virtual on purpose
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal{ name } {}
    std::string_view speak() const { return "Meow"; }
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal{ name } {}
    std::string_view speak() const { return "Woof"; }
};

void describe(const Animal& a) {
    // Through Animal&, speak() is statically resolved to Animal::speak().
    std::cout << a.getName() << " says " << a.speak() << '\n';
}

int main() {
    Cat fred{ "Fred" };
    Dog garbo{ "Garbo" };

    // Direct calls — static type matches dynamic type, derived speak() runs.
    std::cout << "Direct: " << fred.getName() << " says " << fred.speak() << '\n';
    std::cout << "Direct: " << garbo.getName() << " says " << garbo.speak() << '\n';

    // Via Base& — the name comes through (Base data) but speak() is Animal::speak().
    describe(fred);
    describe(garbo);

    // Via Base* — same story.
    const Animal* pa = &fred;
    std::cout << "Base*:  " << pa->getName() << " says " << pa->speak() << '\n';
}
