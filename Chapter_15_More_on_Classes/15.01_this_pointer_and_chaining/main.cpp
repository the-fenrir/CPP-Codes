// 15.1 — `this`, and chaining setters via `return *this;`.
#include <iostream>
#include <string>

class GreetingBuilder {
    std::string m_greeting{ "Hello" };
    std::string m_name{ "world" };
    bool m_loud{ false };
public:
    GreetingBuilder& greeting(std::string g) {
        this->m_greeting = std::move(g);  // `this->` makes the member explicit
        return *this;                      // chainable: returns the current object by ref
    }
    GreetingBuilder& name(std::string n)    { m_name = std::move(n); return *this; }
    GreetingBuilder& loud(bool b = true)    { m_loud = b;            return *this; }

    void print() const {
        std::string s = m_greeting + ", " + m_name + (m_loud ? "!!!" : ".");
        std::cout << s << '\n';
    }
};

int main() {
    GreetingBuilder b;
    b.greeting("Hi").name("Anjaneya").loud().print();
    b.greeting("Hello").name("there").loud(false).print();
}
