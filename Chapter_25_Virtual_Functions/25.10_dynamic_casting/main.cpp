// 25.10 — dynamic_cast: type-checked downcast for polymorphic hierarchies.
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

class Animal {
protected:
    std::string m_name;
    Animal(std::string_view name) : m_name{ name } {}
public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const = 0;
    virtual ~Animal() = default;
};

class Cat : public Animal {
public:
    Cat(std::string_view name) : Animal{ name } {}
    std::string_view speak() const override { return "Meow"; }
    void purr() const { std::cout << "  " << m_name << " purrs.\n"; }
};

class Dog : public Animal {
public:
    Dog(std::string_view name) : Animal{ name } {}
    std::string_view speak() const override { return "Woof"; }
};

// Generic on Animal*, but opportunistically reaches for Cat behavior.
void interact(const Animal* a) {
    std::cout << a->getName() << " says " << a->speak() << '\n';
    if (const auto* cat = dynamic_cast<const Cat*>(a))
        cat->purr();                                  // only on real Cats
    else
        std::cout << "  (no purr — not a Cat)\n";
}

int main() {
    Cat fred{ "Fred" };
    Dog garbo{ "Garbo" };
    interact(&fred);   // purrs
    interact(&garbo);  // doesn't

    // Reference form throws on failure.
    try {
        Animal& a = garbo;
        [[maybe_unused]] auto& c = dynamic_cast<Cat&>(a); // throws
    } catch (const std::bad_cast& e) {
        std::cout << "bad_cast caught: " << e.what() << '\n';
    }
}
