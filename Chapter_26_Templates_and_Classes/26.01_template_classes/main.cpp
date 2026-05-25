// 26.1 — class template with member functions defined inside and outside the class body.
#include <cassert>
#include <iostream>

template <typename T>
class Array {
    int m_length{};
    T*  m_data{};
public:
    explicit Array(int length) : m_length{ length }, m_data{ new T[static_cast<unsigned>(length)]{} } {}
    ~Array() { delete[] m_data; }

    // Non-copyable for this demo — keeps the focus on templates, not rule-of-three.
    Array(const Array&)            = delete;
    Array& operator=(const Array&) = delete;

    int length() const { return m_length; }

    // Declared here, defined below the class.
    T& operator[](int index);
};

// Out-of-line definition: repeat the template header, qualify the class with <T>.
template <typename T>
T& Array<T>::operator[](int index) {
    assert(index >= 0 && index < m_length);
    return m_data[index];
}

int main() {
    Array<int> ints{ 4 };
    for (int i{ 0 }; i < ints.length(); ++i) ints[i] = i * i;

    Array<double> doubles{ 3 };
    doubles[0] = 1.5; doubles[1] = 2.5; doubles[2] = 3.5;

    std::cout << "ints:    "; for (int i{ 0 }; i < ints.length();    ++i) std::cout << ints[i]    << ' '; std::cout << '\n';
    std::cout << "doubles: "; for (int i{ 0 }; i < doubles.length(); ++i) std::cout << doubles[i] << ' '; std::cout << '\n';

    // Array<int> and Array<double> are *different types*: no implicit conversion between them.
    // Array<int> bad = doubles; // would not compile.
}
