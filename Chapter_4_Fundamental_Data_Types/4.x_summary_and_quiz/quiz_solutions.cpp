// Chapter 4 quiz solutions.
//   Q1: typed declarations with rationale
//   Q2: calculator (driven by a fixed istringstream so output is deterministic)
//   Q3: falling-ball simulation
//
// Build/run via the chapter's catch-all target:  make 4.x
#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>

// ── Q1: pick the right type ─────────────────────────────────────────
//
// Design notes:
//  • Quantities → signed types (lesson 4.5). Unsigned only when we deliberately
//    want modular wrap, or for bit twiddling.
//  • Real numbers → double by default; drop to float only when the spec actually
//    pressures on size.
//  • Pin a fixed width with <cstdint> when the size matters semantically
//    (e.g. "birth year fits in 16 bits").
void q1_demo() {
    int           age              { 28      };   // (a) size unimportant → int
    bool          wants_updates    { true    };   // (b) yes/no → bool
    double        pi               { 3.14159265358979 }; // (c) lots of digits → double
    int           pages            { 850     };   // (d) size unimportant → int
    float         couch_feet       { 6.50f   };   // (e) size important, real number → float
    std::int32_t  lifetime_blinks  { 500000000 }; // (f) millions/billions, pinned width
    char          menu_choice      { 'A'     };   // (g) single character → char
    std::int16_t  birth_year       { 1997    };   // (h) size matters, fits in 16 bits

    std::cout << "── Q1 ──\n";
    std::cout << "age            = " << age              << '\n';
    std::cout << "wants_updates  = " << std::boolalpha << wants_updates << '\n';
    std::cout << "pi             = " << pi               << '\n';
    std::cout << "pages          = " << pages            << '\n';
    std::cout << "couch_feet     = " << couch_feet       << '\n';
    std::cout << "lifetime_blinks= " << lifetime_blinks  << '\n';
    std::cout << "menu_choice    = " << menu_choice      << '\n';
    std::cout << "birth_year     = " << birth_year       << '\n';
}

// ── Q2: calculator ──────────────────────────────────────────────────
//
// Design notes:
//  • Operator goes in via a `char`, not a string — single-character menu choice.
//  • Invalid operator: produce no output (per the spec). Don't print "error",
//    don't throw — just silently do nothing.
//  • Division by zero on doubles is well-defined (yields ±Inf), but most callers
//    would want it flagged. Spec doesn't ask, so we don't.
//  • Driving from an istringstream instead of std::cin so the example runs
//    deterministically under `make 4.x`. To make it interactive, replace `in`
//    with `std::cin`.
void calculator(std::istream& in) {
    double x{}, y{};
    char op{};

    std::cout << "Enter a double value: ";
    in >> x;
    std::cout << x << '\n';

    std::cout << "Enter a double value: ";
    in >> y;
    std::cout << y << '\n';

    std::cout << "Enter +, -, *, or /: ";
    in >> op;
    std::cout << op << '\n';

    if (op == '+')      std::cout << x << " + " << y << " is " << (x + y) << '\n';
    else if (op == '-') std::cout << x << " - " << y << " is " << (x - y) << '\n';
    else if (op == '*') std::cout << x << " * " << y << " is " << (x * y) << '\n';
    else if (op == '/') std::cout << x << " / " << y << " is " << (x / y) << '\n';
    // Any other operator → no output, per the spec.
}

// ── Q3: falling ball ────────────────────────────────────────────────
//
// Design notes:
//  • Two functions per learncpp's hint: a pure calculator and a printer.
//  • calculateHeight clamps to 0 — once the ball has fallen past the tower's
//    base, "negative height" is meaningless. Printer then branches on that.
//  • Gravity constant is a `constexpr double` so the compiler can fold it.
namespace falling {
    constexpr double g{ 9.8 }; // m/s²

    double calculateHeight(double towerHeight, int seconds) {
        const double fallen = g * seconds * seconds / 2.0;
        const double height = towerHeight - fallen;
        return (height < 0.0) ? 0.0 : height;
    }

    void printBallHeight(double towerHeight, int seconds) {
        const double h = calculateHeight(towerHeight, seconds);
        if (h > 0.0) {
            std::cout << "At " << seconds << " seconds, the ball is at height: "
                      << h << " meters\n";
        } else {
            std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
        }
    }
}

int main() {
    q1_demo();

    std::cout << "\n── Q2: calculator ──\n";
    // Fixed input: "6.2 5 *"  → expect  "6.2 * 5 is 31"
    std::istringstream in{ "6.2 5 *" };
    calculator(in);

    std::cout << "\n── Q3: falling ball (tower height 100 m) ──\n";
    const double towerHeight{ 100.0 };
    for (int t{ 0 }; t <= 5; ++t) {
        falling::printBallHeight(towerHeight, t);
    }
}
