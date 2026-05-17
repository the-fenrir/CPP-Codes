// 2.2 — value-returning functions feed their result into expressions.
#include <iostream>

int getAnswer() {
    return 42;                       // hands a value back to the caller
}

int doubleIt(int x) {
    return x * 2;
}

int main() {
    std::cout << "answer  = " << getAnswer() << '\n';
    std::cout << "doubled = " << doubleIt(getAnswer()) << '\n'; // composable

    int stored{ getAnswer() };       // or store it
    std::cout << "stored  = " << stored << '\n';
    // main implicitly returns 0
}
