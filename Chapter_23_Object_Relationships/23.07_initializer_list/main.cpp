// 23.7 — IntArray + std::initializer_list. Adds brace-init and brace-assign.
// Also shows the "list constructor wins" trap.
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <iostream>

class IntArray {
    int* m_data{ nullptr };
    int  m_size{ 0 };
public:
    IntArray() = default;
    explicit IntArray(int size) : m_data{ new int[size]{} }, m_size{ size } {}

    // The new bit. Delegate allocation to IntArray(int), then copy in the elements.
    IntArray(std::initializer_list<int> list) : IntArray(static_cast<int>(list.size())) {
        std::copy(list.begin(), list.end(), m_data);
    }

    ~IntArray() { delete[] m_data; }

    IntArray(const IntArray& other) : m_data{ new int[other.m_size] }, m_size{ other.m_size } {
        std::copy(other.m_data, other.m_data + m_size, m_data);
    }
    IntArray& operator=(const IntArray& other) {
        if (this == &other) return *this;
        delete[] m_data;
        m_size = other.m_size;
        m_data = new int[m_size];
        std::copy(other.m_data, other.m_data + m_size, m_data);
        return *this;
    }

    // Brace-assignment: a = { 9, 8, 7 };
    IntArray& operator=(std::initializer_list<int> list) {
        const int newSize = static_cast<int>(list.size());
        if (newSize != m_size) {
            delete[] m_data;
            m_data = new int[newSize];
            m_size = newSize;
        }
        std::copy(list.begin(), list.end(), m_data);
        return *this;
    }

    int  size() const { return m_size; }
    int& operator[](int i)       { assert(i >= 0 && i < m_size); return m_data[i]; }
    int  operator[](int i) const { assert(i >= 0 && i < m_size); return m_data[i]; }
};

static void dump(const char* label, const IntArray& a) {
    std::cout << label << " size=" << a.size() << " [";
    for (int i = 0; i < a.size(); ++i) std::cout << (i ? "," : "") << a[i];
    std::cout << "]\n";
}

int main() {
    IntArray a{ 1, 3, 5, 7, 9 };      // list constructor
    dump("a{1,3,5,7,9}", a);

    IntArray b = { 2, 4, 6 };         // copy-list-init — still the list ctor
    dump("b={2,4,6}   ", b);

    a = { 100, 200 };                  // initializer_list assignment
    dump("a={100,200} ", a);

    // ── The trap ────────────────────────────────────────────────
    IntArray  five_elems(5);          // parens → IntArray(int): five zeros
    IntArray  one_elem{ 5 };          // braces → list ctor: one element with value 5
    dump("(5) means    ", five_elems);
    dump("{5} means    ", one_elem);
}
