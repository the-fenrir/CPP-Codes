// 1.4 — initialization forms.
#include <iostream>

int main()
{
    int a = 5;       // copy-init        (legacy C style)
    int b(5);        // direct-init      (function-call style)
    int c{ 5 };      // direct-list-init (preferred — brace-init)
    int d{};         // value-init       (zero-initializes: d == 0)

    std::cout << "a=" << a << " b=" << b << " c=" << c << " d=" << d << '\n';

    // Assignment after initialization:
    c = 10;
    std::cout << "c after assignment = " << c << '\n';

    // Brace-init rejects narrowing conversions.
    // int bad{ 4.5 };       // ← would be a compile error: double → int narrows
    // int ok = 4.5;         // ← copy-init compiles but silently truncates 4.5 → 4
    //                          (and typically emits a -Wliteral-conversion warning).
    //
    // Demonstrating the *same* truncation without tripping the build's
    // -Wliteral-conversion: a runtime double truncates the same way.
    double from{ 4.5 };
    int    ok{ static_cast<int>(from) };   // explicit cast = "yes I really mean it"
    std::cout << "ok = " << ok << " (cast from " << from << ")\n";

    return 0;
}
