// 21.12 — copy assignment with self-assignment check.
// (Real code: use std::string. This is the teaching example.)
#include <cstring>
#include <iostream>

class MyString {
    char*       m_data{ nullptr };
    std::size_t m_len{ 0 };
public:
    MyString() = default;

    MyString(const char* s) : m_len{ std::strlen(s) } {
        m_data = new char[m_len + 1];
        std::strcpy(m_data, s);
    }

    // Copy constructor (rule of three: needed alongside operator=).
    MyString(const MyString& other) : m_len{ other.m_len } {
        m_data = new char[m_len + 1];
        std::strcpy(m_data, other.m_data ? other.m_data : "");
    }

    // Copy assignment.
    MyString& operator=(const MyString& rhs) {
        if (this == &rhs) return *this;       // self-assignment guard
        delete[] m_data;                      // release current resource
        m_len  = rhs.m_len;
        m_data = new char[m_len + 1];
        std::strcpy(m_data, rhs.m_data ? rhs.m_data : "");
        return *this;                         // enable chaining
    }

    ~MyString() { delete[] m_data; }

    const char* c_str() const { return m_data ? m_data : ""; }
};

int main() {
    MyString a{ "hello" };
    MyString b;
    b = a;                  // copy assignment
    std::cout << "b = " << b.c_str() << '\n';

    MyString c;
    c = a = b;              // chaining: works because operator= returns *this
    std::cout << "c = " << c.c_str() << '\n';

    // Self-assignment must not crash. The compiler knows this pattern is
    // suspicious — silence the warning since it's deliberate for the test.
#if defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wself-assign-overloaded"
#endif
    a = a;
#if defined(__clang__)
#  pragma clang diagnostic pop
#endif
    std::cout << "a = " << a.c_str() << '\n';
}
