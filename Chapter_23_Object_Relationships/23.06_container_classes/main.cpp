// 23.6 — IntArray: a hand-rolled value container that owns its storage.
// All the moving parts of a tiny std::vector<int>, with comments calling
// out *why* each piece has to exist.
#include <cassert>
#include <iostream>

class IntArray {
    int* m_data{ nullptr };
    int  m_size{ 0 };
public:
    IntArray() = default;
    explicit IntArray(int size) : m_data{ new int[size]{} }, m_size{ size } {}

    // Rule of three — we own a heap buffer, so copy must deep-copy and dtor must free.
    ~IntArray() { delete[] m_data; }

    IntArray(const IntArray& other) : m_data{ new int[other.m_size] }, m_size{ other.m_size } {
        for (int i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
    }
    IntArray& operator=(const IntArray& other) {
        if (this == &other) return *this;
        delete[] m_data;
        m_size = other.m_size;
        m_data = new int[m_size];
        for (int i = 0; i < m_size; ++i) m_data[i] = other.m_data[i];
        return *this;
    }

    int  size() const { return m_size; }
    int& operator[](int i)       { assert(i >= 0 && i < m_size); return m_data[i]; }
    int  operator[](int i) const { assert(i >= 0 && i < m_size); return m_data[i]; }

    // Fast but destructive: throws away old contents.
    void reallocate(int newSize) {
        delete[] m_data;
        m_data = (newSize > 0) ? new int[newSize]{} : nullptr;
        m_size = newSize;
    }

    // Slower; preserves what fits.
    void resize(int newSize) {
        if (newSize == m_size) return;
        int* buf = (newSize > 0) ? new int[newSize]{} : nullptr;
        const int n = (newSize < m_size) ? newSize : m_size;
        for (int i = 0; i < n; ++i) buf[i] = m_data[i];
        delete[] m_data;
        m_data = buf;
        m_size = newSize;
    }

    void insertBefore(int value, int index) {
        assert(index >= 0 && index <= m_size);
        int* buf = new int[m_size + 1];
        for (int i = 0; i < index;  ++i) buf[i]     = m_data[i];
        buf[index] = value;
        for (int i = index; i < m_size; ++i) buf[i+1] = m_data[i];
        delete[] m_data;
        m_data = buf;
        ++m_size;
    }

    void remove(int index) {
        assert(index >= 0 && index < m_size);
        if (m_size == 1) { erase(); return; }
        int* buf = new int[m_size - 1];
        for (int i = 0; i < index;       ++i) buf[i]   = m_data[i];
        for (int i = index + 1; i < m_size; ++i) buf[i-1] = m_data[i];
        delete[] m_data;
        m_data = buf;
        --m_size;
    }

    void erase() { delete[] m_data; m_data = nullptr; m_size = 0; }
};

static void dump(const char* label, const IntArray& a) {
    std::cout << label << " [";
    for (int i = 0; i < a.size(); ++i) std::cout << (i ? "," : "") << a[i];
    std::cout << "] size=" << a.size() << '\n';
}

int main() {
    IntArray a{ 5 };
    for (int i = 0; i < a.size(); ++i) a[i] = (i + 1) * 10;
    dump("init    ", a);

    a.insertBefore(25, 2);   dump("ins 25@2", a);
    a.remove(0);             dump("rm    0 ", a);
    a.resize(8);             dump("resz  8 ", a);   // preserves
    a.reallocate(3);         dump("realloc3", a);   // wipes

    IntArray b = a;          // deep copy
    b[0] = 999;
    dump("a (unchanged)", a);
    dump("b (modified) ", b);
}
