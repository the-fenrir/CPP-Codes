// 24.2 — Basic mechanics of public inheritance.
//   Employee : public Person.
//   Employee inherits Person's data + member functions, then adds salary.
#include <iostream>
#include <string>

class Person {
public:
    std::string m_name{};
    int         m_age{};

    Person(std::string name, int age) : m_name{ std::move(name) }, m_age{ age } {}

    void greet() const {
        std::cout << "Hi, I'm " << m_name << ".\n";
    }
};

class Employee : public Person {
public:
    double m_salary{};

    Employee(std::string name, int age, double salary)
        : Person{ std::move(name), age }, m_salary{ salary } {}

    void describe() const {
        // greet() came from Person — accessible directly.
        greet();
        std::cout << "  I'm " << m_age << " and earn $" << m_salary << ".\n";
    }
};

int main() {
    Employee e{ "Lin", 29, 75000 };
    e.describe();
}
