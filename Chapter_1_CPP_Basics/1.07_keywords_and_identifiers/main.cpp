// 1.7 — identifiers: legal vs. illegal, good vs. bad names.
#include <iostream>

int main()
{
    // Legal identifiers.
    int retries{ 3 };
    int max_retries{ 5 };
    int Retries2{ 7 };           // different from `retries` — case-sensitive

    // Compare to bad names (legal but uninformative):
    int n{ 3 };                  // n what? items? retries? bytes?
    int data{ 5 };               // "data" is so generic it might as well be x

    std::cout << "retries     = " << retries     << '\n';
    std::cout << "max_retries = " << max_retries << '\n';
    std::cout << "Retries2    = " << Retries2    << '\n';
    std::cout << "n           = " << n           << "  (bad: meaning unclear)\n";
    std::cout << "data        = " << data        << "  (bad: meaning unclear)\n";

    // ILLEGAL (uncomment to see the compiler complain):
    //   int 2cool;   // starts with digit
    //   int return;  // keyword
    //   int my-var;  // '-' is not allowed in identifiers

    return 0;
}
