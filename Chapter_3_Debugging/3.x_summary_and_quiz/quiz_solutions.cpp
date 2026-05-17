// Chapter 3 quiz solutions.
//   Q1: pass-by-value vs return value
//   Q2: typo — assigning to x twice instead of x then y
//   Q3: call stack — discussion, see NOTES.md
//   Q4: reading into a char and returning as int
//
// To avoid interactive input here, the "readNumber" functions are stubbed
// to return scripted values. The bug + fix pattern is identical to the
// original learncpp programs.
#include <iostream>

// ── Q1 ──────────────────────────────────────────────────────────────
//
// Original (buggy) shape, annotated:
//
//   int readNumber(int x) {                // x is a copy — modifying it
//       std::cin >> x;                     // here doesn't affect the caller
//       return x;
//   }
//
//   readNumber(x);                         // BUG: discards the return value
//   x = x + readNumber(x);                 // reads a second number, OK
//
// Root cause: `readNumber(x);` reads a number into the *local copy* x and
// then throws the return value away. The caller's x is unchanged. So the
// "sum" is `0 + (second number)`.
//
// Fix: capture the return value (and stop pretending the parameter is an
// output parameter — drop it):

namespace q1 {
int counter{ 0 };
int readNumber() {                          // no parameter at all
    static int scripted[] = { 7, 11 };      // pretend the user typed these
    return scripted[counter++];
}
void writeAnswer(int x) {
    std::cout << "Q1: sum = " << x << "  (expect 18)\n";
}
void run() {
    int x{ readNumber() };
    x = x + readNumber();                   // capture both return values
    writeAnswer(x);
}
}

// ── Q2 ──────────────────────────────────────────────────────────────
//
// Original (buggy):
//
//   x = readNumber();    // first  input → x
//   x = readNumber();    // BUG: second input also lands in x; y stays 0
//   writeAnswer(x / y);  // division by zero
//
// Root cause: copy-paste typo. The second assignment should target `y`.
// `y` is value-initialized to 0, so the division blows up.
//
// Fix: assign the second number to y.

namespace q2 {
int counter{ 0 };
int readNumber() {
    static int scripted[] = { 8, 4 };
    return scripted[counter++];
}
void writeAnswer(int x) {
    std::cout << "Q2: quotient = " << x << "  (expect 2)\n";
}
void run() {
    int x{ 0 };
    int y{ 0 };
    x = readNumber();
    y = readNumber();                       // FIX: was `x = readNumber();`
    writeAnswer(x / y);
}
}

// ── Q4 ──────────────────────────────────────────────────────────────
//
// Original (buggy):
//
//   int readNumber() {
//       char x{};            // BUG: reading into a char
//       std::cin >> x;       // reads ONE character, not a number
//       return x;            // returns its ASCII value (cast to int)
//   }
//
// Input '2' → char x = '2' → numeric value 50 (ASCII).
// Input '3' → char x = '3' → numeric value 51.
// Sum: 50 + 51 = 101.  Matches the observed wrong output exactly.
//
// Fix: read into an int.

namespace q4 {
int counter{ 0 };
int readNumber() {
    static int scripted[] = { 2, 3 };
    return scripted[counter++];             // simulating cin >> int_var
}
void writeAnswer(int x) {
    std::cout << "Q4: sum = " << x << "  (expect 5)\n";
}
void run() {
    int x{ readNumber() };
    int y{ readNumber() };
    writeAnswer(x + y);
}
}

int main() {
    q1::run();
    q2::run();
    // Q3 is a discussion question — see NOTES.md.
    q4::run();
}
