// 21.9 — two operator[] overloads: mutable & const. Return by reference.
#include <cassert>
#include <cstddef>
#include <iostream>

class IntList {
    static constexpr std::size_t N = 4;
    int m_data[N]{};
public:
    int& operator[](std::size_t i) {
        assert(i < N && "IntList index out of range");
        return m_data[i];
    }
    const int& operator[](std::size_t i) const {
        assert(i < N && "IntList index out of range");
        return m_data[i];
    }
    std::size_t size() const { return N; }
};

void dump(const IntList& list) {        // can call only the `const` overload here
    for (std::size_t i = 0; i < list.size(); ++i)
        std::cout << list[i] << ' ';
    std::cout << '\n';
}

int main() {
    IntList list;
    list[0] = 10;
    list[1] = 20;
    list[2] = 30;
    list[3] = 40;
    dump(list);
}
