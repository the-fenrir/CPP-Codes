// 26.5 — partial specialization: pin some parameters, leave others free.
#include <cstddef>
#include <iostream>

// Primary template.
template <typename T, std::size_t N>
class StaticArray {
    T m_data[N]{};
public:
    constexpr std::size_t size() const { return N; }
    T&       operator[](std::size_t i)       { return m_data[i]; }
    const T& operator[](std::size_t i) const { return m_data[i]; }

    void print() const {
        for (std::size_t i{ 0 }; i < N; ++i) std::cout << m_data[i] << ' ';
        std::cout << '\n';
    }
};

// Partial specialization for char arrays: keep N free, pin T = char.
// Same interface, but print() treats the buffer as text.
template <std::size_t N>
class StaticArray<char, N> {
    char m_data[N]{};
public:
    constexpr std::size_t size() const { return N; }
    char&       operator[](std::size_t i)       { return m_data[i]; }
    const char& operator[](std::size_t i) const { return m_data[i]; }

    void print() const {
        // Stop at the first null so it behaves like a C-string.
        for (std::size_t i{ 0 }; i < N && m_data[i] != '\0'; ++i) std::cout << m_data[i];
        std::cout << '\n';
    }
};

int main() {
    StaticArray<int, 4> ints;
    ints[0] = 1; ints[1] = 4; ints[2] = 9; ints[3] = 16;
    ints.print();  // primary template

    StaticArray<char, 14> word;
    const char src[] = "Hello, world!";
    for (std::size_t i{ 0 }; i < sizeof(src); ++i) word[i] = src[i];
    word.print();  // partial specialization for char — prints as a string
}
