// 26.2 — non-type template parameters: size lives in the type.
#include <cstddef>
#include <iostream>

template <typename T, std::size_t N>
class StaticArray {
    T m_data[N]{};   // stack-allocated, size known at compile time.
public:
    constexpr std::size_t size() const { return N; }
    T&       operator[](std::size_t i)       { return m_data[i]; }
    const T& operator[](std::size_t i) const { return m_data[i]; }
};

int main() {
    StaticArray<int,    4> ints;
    StaticArray<double, 3> doubles;

    for (std::size_t i{ 0 }; i < ints.size(); ++i)    ints[i] = static_cast<int>(i * i);
    for (std::size_t i{ 0 }; i < doubles.size(); ++i) doubles[i] = 0.5 + static_cast<double>(i);

    std::cout << "ints[" << ints.size() << "]:    ";
    for (std::size_t i{ 0 }; i < ints.size(); ++i) std::cout << ints[i] << ' ';
    std::cout << '\n';

    std::cout << "doubles[" << doubles.size() << "]: ";
    for (std::size_t i{ 0 }; i < doubles.size(); ++i) std::cout << doubles[i] << ' ';
    std::cout << '\n';

    // The size is part of the type — the compiler can reason about it statically.
    static_assert(sizeof(StaticArray<int, 4>) >= 4 * sizeof(int));
    static_assert(!std::is_same_v<StaticArray<int, 4>, StaticArray<int, 5>>);
}
