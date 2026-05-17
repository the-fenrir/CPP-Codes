// 5.7 — std::string: construction, concatenation, length, getline, the
//       >> / getline mix-up, and passing by const&.
#include <iostream>
#include <string>

// Take strings by const-ref to avoid copying.
void greet(const std::string& who) {
    std::cout << "hello, " << who << "!\n";
}

int main() {
    std::string first{ "Ada" };
    std::string last { "Lovelace" };

    // Concatenation. `first + " " + last` allocates one temporary.
    std::string full = first + " " + last;
    std::cout << "full name: " << full
              << "  (length = " << full.length() << ")\n";

    // Value comparison — not pointer comparison.
    std::cout << std::boolalpha << "Ada == Ada? " << (first == std::string{ "Ada" }) << '\n';

    greet(full);

    // Reading input.
    //   `std::cin >> n` leaves a newline in the buffer. The next
    //   std::getline would then read an empty line. `std::cin >> std::ws`
    //   discards leading whitespace (including that lingering newline).
    std::cout << "enter your age: ";
    int age{};
    std::cin >> age;

    std::cout << "enter your full name: ";
    std::string name;
    std::getline(std::cin >> std::ws, name);

    std::cout << name << " is " << age << " years old.\n";
}
