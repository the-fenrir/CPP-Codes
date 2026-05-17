// Chapter 10 quiz solutions.
//   Q1:   discussion table — see NOTES.md
//   Q2a:  degree-to-radian conversion with type aliases
//   Q2b:  discussion — why `radians = degrees;` compiles
//
// Q2a design notes:
//  * `using` form preferred over `typedef` — reads left-to-right and
//    composes with templates if we ever generalize.
//  * Function signatures `Radians convertToRadians(Degrees)` are the whole
//    point: at the call site, intent is documented.
//  * BUT aliases give no type safety (see Q2b). The compiler will happily
//    pass a Degrees where a Radians is wanted, because both are `double`.
//    To get real safety you'd wrap each in a struct. We deliberately stay
//    with aliases here — the exercise is about aliases.
//  * No std::cin call in this driver: the original prompt reads from cin,
//    but a non-interactive run is easier to verify. We hardcode a sample.

#include <iostream>

namespace constants
{
    constexpr double pi{ 3.14159 };
}

using Degrees = double;
using Radians = double;

Radians convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    // Original prompt reads from cin; we use a fixed input to keep the
    // build's `make 10.x` non-interactive.
    Degrees degrees{ 90.0 };

    Radians radians{ convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    // Q2b demonstration: this compiles cleanly even though it's nonsense.
    // Both aliases name `double`, so the compiler sees `double = double`
    // and is satisfied. Type aliases document; they don't enforce.
    radians = degrees;
    std::cout << "after `radians = degrees;` — radians is now "
              << radians << "  (unit confusion, silently accepted)\n";

    return 0;
}
