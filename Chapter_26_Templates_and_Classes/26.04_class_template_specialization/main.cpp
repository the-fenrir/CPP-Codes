// 26.4 — full class template specialization: Storage8<bool> packs bits.
#include <cstdint>
#include <iostream>

// Primary template — 8 elements of T, one slot per element.
template <typename T>
class Storage8 {
    T m_array[8]{};
public:
    void     set(int index, const T& value) { m_array[index] = value; }
    const T& get(int index) const           { return m_array[index]; }
};

// Full specialization for bool — pack 8 bools into a single byte.
template <>
class Storage8<bool> {
    std::uint8_t m_data{ 0 };
public:
    void set(int index, bool value) {
        const std::uint8_t mask = static_cast<std::uint8_t>(1u << index);
        if (value) m_data = static_cast<std::uint8_t>(m_data |  mask);
        else       m_data = static_cast<std::uint8_t>(m_data & ~mask);
    }
    bool get(int index) const {
        return (m_data & (1u << index)) != 0;
    }
};

int main() {
    Storage8<int> ints;
    for (int i{ 0 }; i < 8; ++i) ints.set(i, i * 10);
    std::cout << "ints[3] = " << ints.get(3) << '\n';

    Storage8<bool> flags;
    flags.set(0, true);
    flags.set(3, true);
    flags.set(7, true);
    for (int i{ 0 }; i < 8; ++i) std::cout << flags.get(i);
    std::cout << '\n';

    // The whole point of the specialization: 1 byte instead of 8.
    std::cout << "sizeof(Storage8<int>)  = " << sizeof(Storage8<int>)  << '\n';
    std::cout << "sizeof(Storage8<bool>) = " << sizeof(Storage8<bool>) << '\n';
    static_assert(sizeof(Storage8<bool>) == 1);
}
