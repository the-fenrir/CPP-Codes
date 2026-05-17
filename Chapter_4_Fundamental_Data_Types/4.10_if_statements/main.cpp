// 4.10 — if / else if / else, non-boolean condition, early return.
#include <iostream>

// Predicate function — plugs straight into `if`.
bool isEven(int n) {
    return n % 2 == 0;
}

// Early-return pattern: handle the "nothing to do" case first to flatten the rest.
void describe(int n) {
    if (n == 0) {
        std::cout << "zero\n";
        return;
    }

    if (n > 0) {
        std::cout << n << " is positive and " << (isEven(n) ? "even" : "odd") << '\n';
    } else {
        std::cout << n << " is negative and " << (isEven(n) ? "even" : "odd") << '\n';
    }
}

int main() {
    describe( 0);
    describe( 7);
    describe(-4);

    // Non-boolean condition: `if (x)` means `if (x != 0)`.
    int x{ 3 };
    if (x) {
        std::cout << "x is non-zero (= " << x << ")\n";
    }
}
