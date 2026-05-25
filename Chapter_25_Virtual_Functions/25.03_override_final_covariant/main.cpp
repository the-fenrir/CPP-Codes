// 25.3 — override, final, and covariant return types.
#include <iostream>
#include <string_view>

class Base {
public:
    virtual std::string_view name() const { return "Base"; }
    virtual Base* clone() const { return new Base{*this}; } // virtual ctor idiom
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    // `override`: compiler verifies a base virtual with this signature exists.
    std::string_view name() const override { return "Derived"; }

    // Covariant return type: Derived* narrows Base*.
    Derived* clone() const override { return new Derived{*this}; }
};

// `final` on the method: nobody below can re-override speak().
class Cat : public Base {
public:
    std::string_view name() const override final { return "Cat"; }
};

// `final` on the class: nobody can inherit from SealedDog at all.
class SealedDog final : public Base {
public:
    std::string_view name() const override { return "SealedDog"; }
};

// // The next two lines would fail to compile if uncommented:
// class StillACat : public Cat { std::string_view name() const override; }; // overrides a final method
// class Hound     : public SealedDog {};                                    // inherits from final class

// // And `override` catches a typo:
// class Buggy : public Base {
// public:
//     std::string_view nme() const override; // ERROR: nothing to override
// };

int main() {
    Derived d;
    Base* pb = &d;
    std::cout << pb->name() << '\n';          // Derived (virtual dispatch)

    // Covariance in action: cloning through Derived* yields Derived*.
    Derived* pd = d.clone();
    std::cout << pd->name() << '\n';          // Derived
    delete pd;

    // Same call through Base* yields Base* (statically) but constructs a Derived dynamically.
    Base* pb2 = pb->clone();
    std::cout << pb2->name() << '\n';         // Derived
    delete pb2;

    Cat c;       std::cout << c.name()       << '\n'; // Cat
    SealedDog s; std::cout << s.name()       << '\n'; // SealedDog
}
