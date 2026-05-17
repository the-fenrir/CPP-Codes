// 10.4 — narrowing conversions are rejected inside { ... } initialization.
//
// The lines below marked "// COMPILE ERROR" are *intentionally* commented
// out so the file still builds. Uncomment any one to see the diagnostic.
#include <iostream>

int main() {
    // OK: same type, no conversion.
    int a{ 5 };

    // OK: widening, always fine.
    double c{ 5 };

    // OK: constexpr integer source exactly representable in the destination.
    constexpr int big = 100;
    short s{ big };     // 100 fits in short, source is constexpr — accepted

    std::cout << "a=" << a << " c=" << c << " s=" << s << '\n';

    // The following would all be NARROWING in brace init — compile errors.

    // int bad1 { 5.4 };           // COMPILE ERROR: 5.4 isn't an exact int
    // int bad2 { 5.0f };          // COMPILE ERROR: float -> int is narrowing
    // float bad3 { 5.0 };         // COMPILE ERROR: 5.0 is double; double -> float narrows

    // double -> int is narrowing even with a `nice` literal in many compilers
    // (the FP-to-integer conversion category is itself narrowing). Try it:
    // int bad4 { 5.0 };           // COMPILE ERROR on clang and others

    // Runtime-only knowledge isn't enough; the compiler reasons about types.
    double d = 5.0;
    (void)d;                       // silence "unused variable" — kept for reference
    // int bad5 { d };             // COMPILE ERROR: d isn't constexpr

    // Copy-initialization (=) does NOT enforce this. It just truncates.
    // Avoid for numeric types — use {} instead.
    int loose = static_cast<int>(3.9);
    std::cout << "loose = " << loose << "  (truncated from 3.9 via static_cast)\n";

    // Escape hatch when you really do mean the conversion: explicit cast.
    int forced{ static_cast<int>(3.9) };
    std::cout << "forced = " << forced << '\n';
}
