// 12.12 — return by reference: safe patterns only. Dangling shown in comments.
#include <iostream>
#include <string>

// Safe: the static lives for the program's lifetime.
int& nextId() {
    static int id { 0 };
    return ++id;
}

// Safe: returning a reference to an argument passed by reference.
//       Caller owns the lifetime; we just forward access.
const std::string& longerOf(const std::string& a, const std::string& b) {
    return a.size() >= b.size() ? a : b;
}

// Default: return by value. Copy elision makes this free.
std::string greet(const std::string& name) {
    return "Hello, " + name;
}

// UNSAFE — shown ONLY in comments; do not call.
//
// const std::string& dangling() {
//     std::string local{ "bye" };   // dies at the closing brace
//     return local;                 // reference dangles immediately
// }
//
// int& danglingByParam(int x) {     // x is local to this function
//     return x;                     // dangling once we return
// }

int main() {
    // Safe: return by reference to static
    std::cout << "id = " << nextId() << '\n';
    std::cout << "id = " << nextId() << '\n';
    nextId() = 100;                   // call expression is an lvalue
    std::cout << "id (after assignment) = " << nextId() << '\n';

    // Safe: return reference to a passed-in argument
    std::string a { "short" };
    std::string b { "definitely longer" };
    const std::string& winner { longerOf(a, b) };
    std::cout << "winner = " << winner << '\n';

    // Return by value: the default, and the right choice unless you have a reason.
    std::cout << greet("Anjaneya") << '\n';
}
