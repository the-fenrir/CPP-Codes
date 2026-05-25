// 24.1 — Inheritance is an "is-a" relationship.
// A BaseballPlayer is a Person; it inherits Person's members without
// having to redeclare them.
#include <iostream>
#include <string>

class Person {
public:
    std::string m_name{};
    int         m_age{};

    Person(std::string name, int age) : m_name{ std::move(name) }, m_age{ age } {}
};

// `: public Person` means "BaseballPlayer is-a Person, with the same access on base members".
class BaseballPlayer : public Person {
public:
    double m_battingAverage{};
    int    m_homeRuns{};

    BaseballPlayer(std::string name, int age, double avg, int hr)
        : Person{ std::move(name), age },     // construct the Person part first
          m_battingAverage{ avg },
          m_homeRuns{ hr }
    {}
};

int main() {
    BaseballPlayer p{ "Ada", 31, 0.312, 27 };

    // Members defined in Person are accessible directly — no `.person.` indirection.
    std::cout << p.m_name << " (age " << p.m_age << ")"
              << " avg=" << p.m_battingAverage
              << " hr="  << p.m_homeRuns << '\n';
}
