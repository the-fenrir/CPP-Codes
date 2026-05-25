// 25.9 — slicing: when polymorphism silently goes away.
#include <iostream>
#include <string_view>
#include <vector>

class Base {
public:
    virtual std::string_view name() const { return "Base"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    std::string_view name() const override { return "Derived"; }
};

void byValue(Base b)        { std::cout << "  byValue:        " << b.name() << '\n'; }
void byRef  (const Base& b) { std::cout << "  byRef:          " << b.name() << '\n'; }

int main() {
    Derived d;

    std::cout << "── pass by value (sliced) vs. pass by reference (polymorphic)\n";
    byValue(d);   // "Base" — sliced
    byRef(d);     // "Derived" — virtual dispatch survives

    std::cout << "\n── copy into a Base local (sliced)\n";
    Base copied = d;
    std::cout << "  copied.name() = " << copied.name() << '\n'; // "Base"

    std::cout << "\n── vector<Base> stores SLICED copies\n";
    std::vector<Base> sliced;
    sliced.push_back(d);                         // slices on emplace
    sliced.push_back(Derived{});
    for (const auto& x : sliced)
        std::cout << "  vector<Base>:   " << x.name() << '\n'; // both "Base"

    std::cout << "\n── vector<Base*> preserves polymorphism\n";
    Derived d1, d2;
    std::vector<const Base*> zoo{ &d1, &d2 };
    for (const auto* p : zoo)
        std::cout << "  vector<Base*>:  " << p->name() << '\n'; // both "Derived"
}
