// 24.9 — Multiple inheritance and how to disambiguate same-named members.
#include <iostream>
#include <string>

class Teacher {
public:
    void work() const { std::cout << "Teaching a class.\n"; }
};

class Researcher {
public:
    void work() const { std::cout << "Writing a paper.\n"; }
};

// Inherit from both. The Professor has two `work` members — one from each base.
class Professor : public Teacher, public Researcher {
public:
    std::string m_name{};
    explicit Professor(std::string name) : m_name{ std::move(name) } {}

    void work_day() const {
        std::cout << m_name << ": ";
        Teacher::work();             // qualified: Teacher's version
        std::cout << m_name << ": ";
        Researcher::work();          // qualified: Researcher's version
        // work();                   // ERROR: ambiguous — Teacher::work or Researcher::work?
    }
};

int main() {
    Professor p{ "Dr. Lin" };
    p.work_day();
}
