// 14.7 — returning const& to a member to avoid copies; the dangling-ref footgun.
#include <iostream>
#include <string>

class Person {
    std::string m_name;
public:
    Person(std::string name) : m_name{ std::move(name) } {}

    const std::string& name() const { return m_name; }  // cheap: no copy.
};

Person makePerson() { return Person{ "Temporary Ted" }; }

int main() {
    Person alice{ "Alice" };

    // Safe: alice outlives the reference.
    const std::string& n = alice.name();
    std::cout << n << '\n';

    // DANGLING — do NOT do this. The Person from makePerson() dies at the
    // semicolon, so `bad` references a destroyed string. Compiles, undefined behavior.
    // const std::string& bad = makePerson().name();
    // std::cout << bad << '\n';  // UB

    // Safe alternative: bind the whole object to a const& (extends its lifetime).
    const Person& kept = makePerson();
    std::cout << kept.name() << '\n';
}
