// 1.8 — whitespace doesn't matter to the compiler; formatting matters to readers.
#include <iostream>

int main()
{
    // Same statement, two styles. Both compile.
    int a{ 1 }; int b{ 2 }; int c{ 3 };               // legal but ugly
    int x{ 1 };
    int y{ 2 };
    int z{ 3 };                                       // readable

    std::cout << "abc = " << a << b << c << '\n';
    std::cout << "xyz = " << x << y << z << '\n';

    // Always brace single-line bodies — habit prevents real bugs later.
    if (x < y) {
        std::cout << "x < y\n";
    }

    return 0;
}
