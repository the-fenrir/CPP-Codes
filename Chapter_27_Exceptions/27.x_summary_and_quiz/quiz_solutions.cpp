// Chapter 27 quiz solutions.
//   Q1:    Fraction with throwing constructor + catch in main
//   Q2/Q3: discussion — see NOTES.md
//
// We don't actually read from std::cin here — the build harness runs each
// binary non-interactively, so we simulate the "user input" inline. The
// catch/throw logic is identical to what an interactive version would use.
#include <iostream>
#include <stdexcept>
#include <string>

// ── Q1: Fraction ────────────────────────────────────────────────────
//
// Design notes:
//  • The constructor throws when denominator == 0. That's the whole point —
//    no `Fraction` can exist in an invalid state, so every member function
//    can assume the invariant without rechecking.
//  • We throw `std::runtime_error` (carries a message via what()). A custom
//    derived type would also be fine; for a one-class example it's overkill.
//  • operator<< is a `friend` so it can read the private members without
//    bloating the public interface with a getter for each.
//  • We catch by `const std::exception&` in main (Q2 discussion): broader
//    than runtime_error, so any future exception type (or an unrelated
//    std::bad_alloc) is still handled.
class Fraction {
    int m_numerator;
    int m_denominator;
public:
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
        if (m_denominator == 0)
            throw std::runtime_error{ "Fraction: denominator cannot be zero" };
    }

    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        return os << f.m_numerator << '/' << f.m_denominator;
    }
};

// Helper that runs one "input pair" through the same try/catch shape an
// interactive program would use.
static void run(int numerator, int denominator) {
    std::cout << "Enter the numerator: "   << numerator   << '\n';
    std::cout << "Enter the denominator: " << denominator << '\n';
    try {
        Fraction f{ numerator, denominator };
        std::cout << f << "\n\n";
    } catch (const std::exception& e) {
        // The chapter's expected output is "Invalid denominator"; we also
        // print what() for debuggability.
        std::cout << "Invalid denominator: " << e.what() << "\n\n";
    }
}

int main() {
    std::cout << "── Q1: Fraction ──\n\n";
    run(3, 4);   // valid: prints 3/4
    run(5, 0);   // invalid: throws, caught, "Invalid denominator: ..."
    run(-7, 2);  // valid: prints -7/2
    return 0;
}
