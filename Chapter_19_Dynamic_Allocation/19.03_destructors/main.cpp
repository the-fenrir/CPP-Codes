// 19.3 — destructors and RAII.
//
// IntArray owns a heap allocation. Constructor allocates, destructor frees.
// Copy operations are deleted so we can't accidentally produce two owners of
// the same buffer (the Rule of Three — chapter 22 expands on this).
//
// In modern C++ this whole class is one line: `std::vector<int> data;`.
#include <iostream>

class IntArray {
    int*        m_data;
    std::size_t m_size;
public:
    IntArray(std::size_t size)
        : m_data{ new int[size]{} }, m_size{ size }
    {
        std::cout << "  ctor: allocated " << m_size << " ints at " << m_data << '\n';
    }

    ~IntArray() {
        std::cout << "  dtor: freeing " << m_size << " ints at " << m_data << '\n';
        delete[] m_data;            // matches the new[] in the ctor
    }

    // Rule of Three: disable copies until we implement them correctly,
    // otherwise the default copy would alias m_data and double-delete.
    IntArray(const IntArray&)            = delete;
    IntArray& operator=(const IntArray&) = delete;

    std::size_t size() const { return m_size; }
    int&  operator[](std::size_t i)       { return m_data[i]; }
    int   operator[](std::size_t i) const { return m_data[i]; }
};

void stack_demo() {
    std::cout << "stack_demo: enter\n";
    IntArray a{ 3 };
    a[0] = 10; a[1] = 20; a[2] = 30;
    std::cout << "  values: " << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';
    std::cout << "stack_demo: leave (dtor fires here)\n";
}   // ← a's destructor runs automatically here

int main() {
    stack_demo();

    std::cout << "\nheap_demo:\n";
    IntArray* p{ new IntArray{ 2 } };
    (*p)[0] = 1; (*p)[1] = 2;
    std::cout << "  values: " << (*p)[0] << ' ' << (*p)[1] << '\n';
    delete p;                        // ← p's destructor runs here
    p = nullptr;

    std::cout << "main: exit\n";
}
