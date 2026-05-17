// 2.6 — extracting a named function makes the call site readable.
#include <iostream>

// Without a helper: the *what* is buried in the *how*.
void inlineVersion() {
    int a{ 3 }, b{ 4 };
    // Re-deriving the same expression at every use site is what makes long
    // functions hard to read:
    int h_squared{ a*a + b*b };
    int total_squared{ (a*a + b*b) + (a*a + b*b) }; // duplicated logic
    std::cout << "inline:    h^2 = " << h_squared
              << ", 2*h^2 = " << total_squared << '\n';
}

// With a helper: call site reads as English, and the formula lives in one place.
int hypotenuseSquared(int a, int b) {
    return a*a + b*b;
}

void extractedVersion() {
    const int h_squared{ hypotenuseSquared(3, 4) };
    const int total_squared{ h_squared + h_squared };
    std::cout << "extracted: h^2 = " << h_squared
              << ", 2*h^2 = " << total_squared << '\n';
}

int main() {
    inlineVersion();
    extractedVersion();
}
