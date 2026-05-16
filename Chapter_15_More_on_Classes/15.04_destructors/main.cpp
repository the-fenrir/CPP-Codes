// 15.4 — destructors + RAII: resources cleaned up automatically.
#include <iostream>

class Buffer {
    int*  m_data;
    int   m_size;
public:
    Buffer(int size) : m_data{ new int[size]{} }, m_size{ size } {
        std::cout << "  ctor  size=" << m_size << '\n';
    }
    ~Buffer() {
        std::cout << "  ~dtor size=" << m_size << '\n';
        delete[] m_data;
    }

    // Disable copying so we don't double-free. (Real fix: see 14.14 / smart pointers.)
    Buffer(const Buffer&)            = delete;
    Buffer& operator=(const Buffer&) = delete;
};

int main() {
    std::cout << "1) enter scope\n";
    {
        Buffer a{ 4 };
        Buffer b{ 8 };
        std::cout << "2) doing work\n";
    }   // ← b destroyed, then a destroyed (reverse declaration order)
    std::cout << "3) outside scope\n";
}
