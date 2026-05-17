// Chapter 11 quiz solutions.
//   Q1a/b/c: overload-resolution reasoning (b and c are commented out
//            because they're meant to NOT compile; comments explain why).
//   Q2:      add / mult / sub templates.
//   Q3:      per-type instantiation → per-type static counters.
//   Q4:      template vs. non-template resolution.
#include <iostream>

// ── Q1a ─────────────────────────────────────────────────────────────
//
// short → int is a promotion (tier 2), short → double is a standard
// conversion (tier 3). Promotion wins → "int 5".
namespace q1a {
    void print(int x)    { std::cout << "int "    << x << '\n'; }
    void print(double x) { std::cout << "double " << x << '\n'; }
    void run() {
        short s{ 5 };
        print(s);
    }
}

// ── Q1b (does NOT compile if enabled) ───────────────────────────────
//
// namespace q1b {
//     void print()          { std::cout << "void\n"; }
//     void print(int x = 0) { std::cout << "int "    << x << '\n'; }
//     void print(double x)  { std::cout << "double " << x << '\n'; }
//     void run() {
//         print(5.0f);   // OK on its own
//         print();       // ERROR: ambiguous —
//                        //   matches print() AND print(int=0) via the default.
//                        //   Defaults don't differentiate overloads.
//     }
// }

// ── Q1c (does NOT compile if enabled) ───────────────────────────────
//
// namespace q1c {
//     void print(long x)   { std::cout << "long "   << x << '\n'; }
//     void print(double x) { std::cout << "double " << x << '\n'; }
//     void run() {
//         print(5);        // ERROR: ambiguous — int→long and int→double
//                          //   are both standard conversions (same tier).
//     }
// }

// ── Q2: three little templates ──────────────────────────────────────
//
// Design notes:
//  • add<T>: single template parameter — both args must be the same type.
//    Deduction does no conversions, so add(1, 2.5) would fail. That's the
//    point of step 3.
//  • mult<T>: only the first param is templated. T is deduced from x alone;
//    y is always int. mult(1.2, 3) ⇒ T = double, returns 3.6.
//  • sub<T,U>: two independent type parameters with an `auto` return —
//    needed because the result type depends on both T and U.
template <typename T>
T add(T x, T y) { return x + y; }

template <typename T>
T mult(T x, int y) { return x * y; }

template <typename T, typename U>
auto sub(T x, U y) { return x - y; }

// ── Q3: per-type statics ────────────────────────────────────────────
//
// count<int> and count<double> are *different functions*, each with its
// own static c. Calling count(1) twice increments the int counter;
// count(2.3) starts the double counter at 0; count<double>(1) reuses it.
template <typename T>
int count(T) {
    static int c{ 0 };
    return ++c;
}

// ── Q4: template vs. non-template ───────────────────────────────────
//
// foo(int) is a non-template. foo<T> is a template. On a tie (same conversion
// cost), the non-template wins — so foo(1) goes to the non-template (1+10=11).
// foo(short) — the non-template requires a promotion, the template doesn't,
// so the template wins (2). Explicit <int> or even <> forces template lookup
// only, taking the non-template out of contention.
int foo(int n) { return n + 10; }

template <typename T>
int foo(T n) { return n; }

int main() {
    std::cout << "── Q1a ──\n";
    q1a::run();

    std::cout << "\n── Q2 ──\n";
    std::cout << "add(2, 3)     = " << add(2, 3)     << '\n';   // 5
    std::cout << "add(1.2, 3.4) = " << add(1.2, 3.4) << '\n';   // 4.6
    std::cout << "mult(2, 3)    = " << mult(2, 3)    << '\n';   // 6
    std::cout << "mult(1.2, 3)  = " << mult(1.2, 3)  << '\n';   // 3.6
    std::cout << "sub(3, 2)     = " << sub(3, 2)     << '\n';   // 1
    std::cout << "sub(3.5, 2)   = " << sub(3.5, 2)   << '\n';   // 1.5
    std::cout << "sub(4, 1.5)   = " << sub(4, 1.5)   << '\n';   // 2.5

    std::cout << "\n── Q3 ──\n";
    std::cout << count(1)         << '\n';   // 1   (count<int>)
    std::cout << count(1)         << '\n';   // 2   (count<int>)
    std::cout << count(2.3)       << '\n';   // 1   (count<double>)
    std::cout << count<double>(1) << '\n';   // 2   (count<double>)

    std::cout << "\n── Q4 ──\n";
    std::cout << foo(1)        << '\n';      // 11  (non-template wins exact tie)
    short s{ 2 };
    std::cout << foo(s)        << '\n';      // 2   (template avoids promotion)
    std::cout << foo<int>(4)   << '\n';      // 4   (explicit → template only)
    std::cout << foo<int>(s)   << '\n';      // 2   (explicit → template; s promotes)
    std::cout << foo<>(6)      << '\n';      // 6   (empty <> still forces template)
}
