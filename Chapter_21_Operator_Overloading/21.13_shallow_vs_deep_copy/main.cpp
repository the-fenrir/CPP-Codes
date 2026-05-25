// 21.13 — deep copy is mandatory when owning a raw pointer.
// `BadString` shows what you'd be running into without it (left commented).
#include <cstring>
#include <iostream>
#include <memory>
#include <string>

// ── BadString: copying is disabled so you can't trigger the bug. ──
class BadString {
    char* m_data{ nullptr };
public:
    BadString(const char* s) {
        m_data = new char[std::strlen(s) + 1];
        std::strcpy(m_data, s);
    }
    ~BadString() { delete[] m_data; }

    // If we'd left these defaulted, two BadStrings would point at the same
    // buffer and the second destructor would double-free. Delete them so
    // the compiler refuses incorrect uses up front:
    BadString(const BadString&)            = delete;
    BadString& operator=(const BadString&) = delete;

    const char* c_str() const { return m_data; }
};

// ── MyString: explicit deep copy (rule of three). ──
class MyString {
    char* m_data{ nullptr };
public:
    MyString(const char* s) {
        m_data = new char[std::strlen(s) + 1];
        std::strcpy(m_data, s);
    }
    MyString(const MyString& o) {
        m_data = new char[std::strlen(o.m_data) + 1];
        std::strcpy(m_data, o.m_data);
    }
    MyString& operator=(const MyString& o) {
        if (this == &o) return *this;
        delete[] m_data;
        m_data = new char[std::strlen(o.m_data) + 1];
        std::strcpy(m_data, o.m_data);
        return *this;
    }
    ~MyString() { delete[] m_data; }
    const char* c_str() const { return m_data; }
};

// ── ModernString: don't own raw memory at all. Default everything. ──
struct ModernString {
    std::string data;     // std::string handles deep copy / move for us
};

int main() {
    MyString a{ "hello" };
    MyString b = a;       // deep copy: independent buffers
    std::cout << "a=" << a.c_str() << "  b=" << b.c_str() << '\n';

    ModernString m1{ "world" };
    ModernString m2 = m1; // implicit copy is already deep — std::string does it
    std::cout << "m1=" << m1.data << "  m2=" << m2.data << '\n';

    BadString x{ "fine alone" };
    // BadString y = x;   // would not compile — copy ctor is deleted
    std::cout << "x=" << x.c_str() << '\n';
}
