// 2.13 — design recipe applied: goal → steps → named functions.
//
// Goal:    take a Celsius temperature and print it in Fahrenheit.
// Inputs:  one double, from a hardcoded constant (would normally be cin).
// Output:  one line, "C°C = F°F".
// Steps:   getCelsius() → toFahrenheit() → printResult().
#include <iostream>

double getCelsius() {
    // Hardcoded for repeatable demo. In a real program, read from std::cin.
    return 25.0;
}

double toFahrenheit(double celsius) {
    return celsius * 9.0 / 5.0 + 32.0;
}

void printResult(double celsius, double fahrenheit) {
    std::cout << celsius << "°C = " << fahrenheit << "°F\n";
}

int main() {
    const double c{ getCelsius() };
    const double f{ toFahrenheit(c) };
    printResult(c, f);
}
