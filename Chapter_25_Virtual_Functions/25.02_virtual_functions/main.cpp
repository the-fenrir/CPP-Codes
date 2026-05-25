// 25.2 — virtual makes Base& dispatch to the derived implementation.
#include <iostream>
#include <string_view>

class Animal {
protected:
    std::string m_name;
    Animal(std::string_view name) : m_name{ name } {}
public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const { return "???"; }
    virtual ~Animal() = default; // anticipating 25.04
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal{ name } {}
    std::string_view speak() const override { return "Meow"; }
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal{ name } {}
    std::string_view speak() const override { return "Woof"; }
};

// Same function as 25.01 — only the base's `virtual` changed.
void describe(const Animal& a) {
    std::cout << a.getName() << " says " << a.speak() << '\n';
}

int main() {
    Cat fred{ "Fred" };
    Dog garbo{ "Garbo" };

    describe(fred);   // Fred says Meow
    describe(garbo);  // Garbo says Woof

    // Same through a heterogeneous array of Animal*.
    const Animal* zoo[] = { &fred, &garbo };
    for (const auto* a : zoo)
        std::cout << a->getName() << " says " << a->speak() << '\n';
}
