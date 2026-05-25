// 24.4 — Derived constructors forward to the base via the initializer list.
#include <iostream>
#include <string>

class Base {
public:
    int m_id{};
    explicit Base(int id) : m_id{ id } {
        std::cout << "Base(" << id << ")\n";
    }
};

class Derived : public Base {
public:
    std::string m_label{};

    // First entry: construct the Base subobject. Then derived-only members.
    Derived(int id, std::string label)
        : Base{ id }, m_label{ std::move(label) }
    {
        std::cout << "Derived(" << m_id << ", \"" << m_label << "\")\n";
    }
};

int main() {
    Derived d{ 7, "alpha" };
    std::cout << "id=" << d.m_id << " label=" << d.m_label << '\n';

    // If Base had no default constructor and we omitted `Base{ ... }`,
    // this would not compile — Derived couldn't construct its base part.
}
