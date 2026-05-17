// 4.2 — void as a function return type, plus the preferred empty-param syntax.
#include <iostream>

// Returns nothing — `void` is the only correct return type here.
void greet() {
    std::cout << "hello\n";
}

// Empty parameter list — prefer `()` over `(void)`. Both compile;
// the (void) form is a C carry-over and deprecated style in C++.
int answer() {
    return 42;
}

int main() {
    greet();
    std::cout << "answer = " << answer() << '\n';

    // void x;             // ill-formed: cannot declare a variable of type void
    // void* p = nullptr;  // legal but unusable until you cast it to a real pointer type
}
