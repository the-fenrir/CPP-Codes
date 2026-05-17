// 12.8 — null pointers: nullptr, null checks, and overload resolution.
#include <iostream>

void describe(int* p) {
    if (p) std::cout << "describe(int*): pointer to " << *p << '\n';
    else   std::cout << "describe(int*): null pointer\n";
}

// Two overloads to demonstrate why nullptr (not 0 or NULL) is correct.
void overloaded(int)  { std::cout << "overloaded(int)\n"; }
void overloaded(int*) { std::cout << "overloaded(int*)\n"; }

int main() {
    int* p { nullptr };          // canonical init: explicitly "no target"
    describe(p);

    int x { 42 };
    p = &x;
    describe(p);

    // Idiomatic null checks:
    if (p)        std::cout << "p is non-null, *p = " << *p << '\n';
    if (!p)       std::cout << "(would not print)\n";
    if (p == nullptr) std::cout << "(would not print)\n";

    // Overload resolution: nullptr picks the pointer overload unambiguously.
    overloaded(0);               // int
    overloaded(nullptr);         // int*
    // overloaded(NULL);         // ambiguous or picks int — avoid

    // The safe pattern: check before dereferencing.
    int* maybe { nullptr };
    if (maybe) std::cout << *maybe;  // skipped — no UB
    else       std::cout << "skipped null dereference\n";
}
