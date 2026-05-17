// Chapter 5 quiz solutions.
//   Q1: discussion — see NOTES.md
//   Q2: fixed driving-age program (three issues addressed)
//   Q3: discussion — see NOTES.md
//   Q4: older-of-two-people
//   Q5: discussion — see NOTES.md
//
// The program runs Q2 and Q4 back-to-back. Q4 reads from std::cin; pipe in
// sample input if you want a non-interactive run.
#include <iostream>
#include <string>

// ── Q2: driving-age program, corrected ──────────────────────────────
//
// Fixes vs. the original:
//   1. `age` is `int`, not `std::uint8_t`. uint8_t is a char alias, so
//      `std::cin >> age` would have read a *character*, not a number.
//   2. The magic `16` is replaced with a named constant `minDrivingAge`.
//      Constexpr makes it usable anywhere a constant expression is needed
//      and documents the value's role at the point of use.
//   3. The bogus multicharacter literal `'.\n'` is replaced with the
//      string literal `".\n"`. Two characters between single quotes is
//      an implementation-defined int, not a 2-char string.
void runQ2() {
    constexpr int minDrivingAge{ 16 };

    std::cout << "How old are you?\n";

    int age{};
    std::cin >> age;

    std::cout << "Allowed to drive a car in Texas: ";
    std::cout << (age >= minDrivingAge ? "Yes" : "No");
    std::cout << ".\n";
}

// ── Q4: older of two people ─────────────────────────────────────────
//
// Design notes:
//  • Names use std::getline so multi-word names ("John Bacon") work.
//  • `std::cin >> age` leaves the trailing newline in the buffer. The
//    next std::getline would read an empty line; `std::cin >> std::ws`
//    discards leading whitespace (including that newline) before the
//    next getline.
//  • A tiny readPerson() helper keeps main() short and avoids duplicating
//    the prompt-then-read-then-flush pattern.
//  • At print time we just pick (older, younger) explicitly — easier to
//    read than nesting a ternary inside the cout chain.
struct Person {
    std::string name;
    int age;
};

Person readPerson(int index) {
    Person p;
    std::cout << "Enter the name of person #" << index << ": ";
    std::getline(std::cin >> std::ws, p.name);

    std::cout << "Enter the age of " << p.name << ": ";
    std::cin >> p.age;

    return p;
}

void runQ4() {
    Person p1{ readPerson(1) };
    Person p2{ readPerson(2) };

    // Q5: neither age1 nor age2 can be `constexpr` — they came from
    // std::cin, which is a runtime input. They could be plain `const`.
    const Person& older   = (p1.age >= p2.age) ? p1 : p2;
    const Person& younger = (p1.age >= p2.age) ? p2 : p1;

    std::cout << older.name   << " (age " << older.age   << ") is older than "
              << younger.name << " (age " << younger.age << ").\n";
}

int main() {
    std::cout << "── Q2: driving age ──\n";
    runQ2();

    std::cout << "\n── Q4: older of two people ──\n";
    runQ4();
}
