// 25.7 — abstract bases and pure interfaces.
#include <iostream>
#include <string>
#include <string_view>

// ── Abstract base: at least one pure virtual ⇒ can't be instantiated.
class Animal {
protected:
    std::string m_name;
    Animal(std::string_view name) : m_name{ name } {}
public:
    const std::string& getName() const { return m_name; }
    virtual std::string_view speak() const = 0; // pure virtual
    virtual ~Animal() = default;
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

// ── Interface class: only pure virtuals, no data, virtual dtor.
class IPrintable {
public:
    virtual void print() const = 0;
    virtual ~IPrintable() = default;
};

class Receipt : public IPrintable {
    double m_total;
public:
    Receipt(double t) : m_total{ t } {}
    void print() const override {
        std::cout << "Receipt: total=$" << m_total << '\n';
    }
};

class Greeting : public IPrintable {
    std::string m_msg;
public:
    Greeting(std::string m) : m_msg{ std::move(m) } {}
    void print() const override {
        std::cout << "Greeting: " << m_msg << '\n';
    }
};

void render(const IPrintable& p) { p.print(); }

int main() {
    // Animal a{"x"}; // ERROR: cannot instantiate abstract class

    Cat fred{ "Fred" };
    Dog garbo{ "Garbo" };
    const Animal* zoo[] = { &fred, &garbo };
    for (auto* a : zoo)
        std::cout << a->getName() << ": " << a->speak() << '\n';

    Receipt  r{ 12.50 };
    Greeting g{ "hello" };
    render(r);
    render(g);
}
