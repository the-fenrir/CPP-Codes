// 4.1 — one variable from each fundamental category.
// Same bits, different interpretations.
#include <cstddef>   // std::nullptr_t
#include <iostream>

int main() {
    int            i  { 42 };          // integer
    double         d  { 3.14159 };     // floating point
    bool           b  { true };        // boolean
    char           c  { 'A' };         // character (integral, prints as char)
    std::nullptr_t np { nullptr };     // null pointer type — only value is nullptr

    std::cout << "int          : " << i  << '\n';
    std::cout << "double       : " << d  << '\n';
    std::cout << "bool         : " << b  << "  (1 = true)\n";
    std::cout << "char         : " << c  << "  (prints as char, stored as integer 65)\n";
    std::cout << "char as int  : " << static_cast<int>(c) << '\n';

    // void is the odd one out: it has no values, so you can't have a void variable.
    // It only appears as a return type (no value) or as void* (covered in chapter 19).
    (void)np;  // silence unused-variable warning
}
