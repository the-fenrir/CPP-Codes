// 23.3 — Aggregation. Department points to Teachers but does NOT own them.
// Teachers were born outside the Department, survive its death, and can be
// referenced from more than one Department at once.
#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Teacher {
    std::string m_name;
public:
    explicit Teacher(std::string name) : m_name{ std::move(name) } {
        std::cout << "  Teacher(" << m_name << ") born\n";
    }
    ~Teacher() { std::cout << "  ~Teacher(" << m_name << ") gone\n"; }
    const std::string& name() const { return m_name; }
};

class Department {
    // reference_wrapper because std::vector<T&> is not a thing.
    std::vector<std::reference_wrapper<const Teacher>> m_teachers;
    std::string m_name;
public:
    explicit Department(std::string name) : m_name{ std::move(name) } {}

    void add(const Teacher& t) { m_teachers.emplace_back(t); }

    void list() const {
        std::cout << m_name << ":";
        for (const Teacher& t : m_teachers) std::cout << ' ' << t.name();
        std::cout << '\n';
    }
    // No destructor that touches m_teachers — they're not ours to delete.
};

int main() {
    Teacher alice{ "Alice" };
    Teacher bob  { "Bob" };
    Teacher carol{ "Carol" };

    {
        Department math{ "Math" };
        Department phys{ "Physics" };

        math.add(alice);  math.add(bob);
        phys.add(bob);    phys.add(carol);   // Bob aggregated by *two* departments

        math.list();
        phys.list();
    }   // ← Departments destroyed here; teachers still alive below

    std::cout << "After reorg, " << alice.name()
              << ", " << bob.name()
              << ", " << carol.name() << " are all still here.\n";
}
