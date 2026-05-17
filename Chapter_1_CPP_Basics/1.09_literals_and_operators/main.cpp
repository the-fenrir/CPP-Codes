// 1.9 — literals and operators.
#include <iostream>

int main()
{
    // Literals: written-out values.
    int    answer { 42 };       // int literal
    double pi     { 3.14 };     // double literal
    char   grade  { 'A' };      // char literal
    bool   ready  { true };     // bool literal

    std::cout << "answer=" << answer
              << " pi=" << pi
              << " grade=" << grade
              << " ready=" << ready << '\n';

    // Operators.
    int x{ 5 };
    int y{ 3 };

    std::cout << "unary  -x  = " << -x      << '\n';   // unary
    std::cout << "binary x+y = " << (x + y) << '\n';   // binary
    std::cout << "binary x<y = " << (x < y) << '\n';   // comparison binary

    // Ternary: condition ? then : else
    int max_xy{ (x > y) ? x : y };
    std::cout << "ternary max(x,y) = " << max_xy << '\n';

    return 0;
}
