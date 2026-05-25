// 17.10 — C-style strings: declare, measure, copy, compare.
#include <cstring>     // strlen, strncpy, strcmp
#include <iostream>

int main() {
    // Size-deduced — 5 chars including the trailing '\0'.
    char name[] { "Alex" };

    std::cout << "name           = " << name << '\n';
    std::cout << "sizeof(name)   = " << sizeof(name)
              << " (includes the null terminator)\n";
    std::cout << "std::strlen(.) = " << std::strlen(name)
              << " (excludes the null terminator)\n";

    // Fixed-size buffer with explicit padding to \0.
    char buf[16] {};                       // all-zero — safe default
    std::strncpy(buf, "hello", sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';           // belt-and-braces terminator
    std::cout << "buf = '" << buf << "'\n";

    // strcmp returns 0 on equal, <0 / >0 on lexicographic order.
    std::cout << "strcmp(\"abc\",\"abc\") = " << std::strcmp("abc", "abc") << '\n';
    std::cout << "strcmp(\"abc\",\"abd\") = " << std::strcmp("abc", "abd") << '\n';

    // Reading user input safely:
    //   std::cin.getline(buf, sizeof(buf));
    // (commented out so the program is non-interactive)
}
