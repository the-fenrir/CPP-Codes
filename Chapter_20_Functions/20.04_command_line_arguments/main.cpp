// 20.4 — command line arguments: enumerate argv and convert the first one safely.
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[]) {
    std::cout << "argc = " << argc << '\n';
    for (int i = 0; i < argc; ++i) {
        // argv[0] is the program invocation; real args start at argv[1].
        std::cout << "  argv[" << i << "] = \"" << argv[i] << "\"\n";
    }

    if (argc >= 2) {
        // Everything arrives as a string. Convert explicitly and handle bad input.
        try {
            int n = std::stoi(argv[1]);
            std::cout << "argv[1] as int = " << n << '\n';
        } catch (const std::invalid_argument&) {
            std::cout << "argv[1] is not a valid integer\n";
        } catch (const std::out_of_range&) {
            std::cout << "argv[1] is out of int range\n";
        }
    } else {
        std::cout << "(pass an argument to try the int conversion, e.g. `./main 42`)\n";
    }
}
