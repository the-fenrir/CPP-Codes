// 7.13 — `using` declarations vs. directives, scoped narrowly.
#include <iostream>
#include <string>

namespace MyLib {
    int count{ 42 };
    void greet() { std::cout << "MyLib::greet\n"; }
}

void safe_usage() {
    using std::cout;            // declaration: just `cout`
    cout << "  cout reached without std:: prefix\n";
    // std::endl etc. still need std::.
}

void scoped_directive() {
    using namespace MyLib;      // directive: every name from MyLib
    greet();
    std::cout << "  MyLib::count = " << count << '\n';
}   // both `greet` and `count` no longer in scope after this brace

int main() {
    safe_usage();
    scoped_directive();

    // greet();    // ERROR: not in scope here (good — the import was local)
    MyLib::greet();
}
