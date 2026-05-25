// 27.5 — class-based exception hierarchy; catch by const Base& to handle a family.
#include <iostream>
#include <stdexcept>
#include <string>

// Base for everything our "array module" throws. Deriving from runtime_error
// gives us the message-carrying constructor and what() for free.
class ArrayError : public std::runtime_error {
public:
    using std::runtime_error::runtime_error; // inherit ctors
};

class IndexError : public ArrayError {
public:
    IndexError(int idx, int size)
        : ArrayError{ "index " + std::to_string(idx) + " out of bounds (size " + std::to_string(size) + ")" } {}
};

class EmptyError : public ArrayError {
public:
    EmptyError() : ArrayError{ "operation on empty array" } {}
};

// A toy array that throws our custom exceptions.
class Array {
    int  m_data[4]{ 10, 20, 30, 40 };
    int  m_size{ 4 };
public:
    int at(int i) const {
        if (m_size == 0) throw EmptyError{};
        if (i < 0 || i >= m_size) throw IndexError{ i, m_size };
        return m_data[i];
    }
};

int main() {
    Array a;

    auto demo = [&](int i) {
        try {
            std::cout << "a.at(" << i << ") = " << a.at(i) << '\n';
        } catch (const IndexError& e) {              // specific first
            std::cout << "IndexError: " << e.what() << '\n';
        } catch (const ArrayError& e) {              // base catches the rest of the family
            std::cout << "ArrayError: " << e.what() << '\n';
        } catch (const std::exception& e) {          // anything else from the std hierarchy
            std::cout << "std::exception: " << e.what() << '\n';
        }
    };

    demo(0);     // ok
    demo(99);    // IndexError
    demo(-1);    // IndexError
    return 0;
}
