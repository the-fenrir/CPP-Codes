// 15.7 — static member functions: factory + class-scoped utility.
#include <iostream>

class Logger {
    inline static int s_count{ 0 };
    int m_id;

    Logger(int id) : m_id{ id } {}    // private — only the factory makes them
public:
    static Logger create() {           // factory: returns a new Logger by value
        return Logger{ ++s_count };
    }
    static int instances() {           // class-scoped read of static state
        return s_count;
    }

    int id() const { return m_id; }
};

int main() {
    auto a = Logger::create();
    auto b = Logger::create();
    std::cout << "a.id=" << a.id() << " b.id=" << b.id() << '\n';
    std::cout << "total: " << Logger::instances() << '\n';
}
