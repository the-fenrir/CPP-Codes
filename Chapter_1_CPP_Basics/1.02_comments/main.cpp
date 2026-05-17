// 1.2 — comment styles, good and bad.
#include <iostream>

/*
 * Block comments are useful for file or function headers.
 * They span multiple lines without needing // on each one.
 */

int main()
{
    // BAD: comment restates the code — adds no information.
    int x{ 5 }; // set x to 5

    // GOOD: comment explains *why* this value was chosen.
    int retries{ 3 }; // 3 retries matches the upstream service's rate-limit window

    std::cout << "x = " << x << ", retries = " << retries << '\n';

    // std::cout << "this line is commented out\n";  // handy for quick debugging

    return 0;
}
