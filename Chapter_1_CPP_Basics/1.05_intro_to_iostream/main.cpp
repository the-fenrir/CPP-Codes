// 1.5 — cout / cin / '\n'.
// NOTE: this lesson normally reads from stdin. To keep `make 1.05` non-interactive,
// we feed it a canned value first and then demonstrate what cin would do.
#include <iostream>

int main()
{
    // Output.
    std::cout << "Hello!\n";
    std::cout << "Chained " << "insertion " << "in one statement.\n";

    // Demonstrate the input pattern without blocking on stdin in CI.
    int x{ 7 };  // pretend the user typed 7
    // Real-world version would be:
    //     std::cout << "Enter an integer: ";
    //     std::cin >> x;
    std::cout << "You entered: " << x << '\n';

    return 0;
}
