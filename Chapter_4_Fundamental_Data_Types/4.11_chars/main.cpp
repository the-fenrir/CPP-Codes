// 4.11 — char as character and integer, arithmetic, escapes.
#include <iostream>

int main() {
    char a{ 'A' };
    char z{ 'z' };

    std::cout << "── char prints as character by default ──\n";
    std::cout << "a = " << a << "   (numeric: " << static_cast<int>(a) << ")\n";
    std::cout << "z = " << z << "   (numeric: " << static_cast<int>(z) << ")\n";

    std::cout << "\n── char arithmetic (it's an integer underneath) ──\n";
    std::cout << "'A' + 1 = " << static_cast<char>(a + 1) << '\n';   // 'B'
    std::cout << "'z' - 'a' = " << (z - 'a') << '\n';                // 25 (alphabet index)

    std::cout << "\n── escape sequences ──\n";
    std::cout << "tab:\there\n";
    std::cout << "newline above\n";
    std::cout << "backslash: \\\n";
    std::cout << "single quote: \'\n";
    std::cout << "double quote: \"\n";

    // 'A' is a char literal (1 byte). "A" is a string literal: a 2-char array {'A','\0'}.
    char        ch{ 'A' };
    const char* s { "A" };
    std::cout << "'A' is a char: " << ch << "   (size " << sizeof('A') << ")\n";
    std::cout << "\"A\" is a string of length 1 (plus '\\0'): " << s << '\n';
}
