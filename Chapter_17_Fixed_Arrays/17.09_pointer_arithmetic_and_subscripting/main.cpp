// 17.9 — pointer arithmetic, subscripting as syntactic sugar.
#include <cstddef>
#include <iostream>
#include <iterator>

int main() {
    int arr[] { 10, 20, 30, 40, 50 };
    int* p { arr };  // decays to a pointer to arr[0]

    // arr[i] is defined as *(arr + i).
    std::cout << "arr[2]      = " << arr[2] << '\n';
    std::cout << "*(arr + 2)  = " << *(arr + 2) << '\n';

    // Walk the array with pointer arithmetic, iterator-style.
    std::cout << "iter walk  :";
    for (int* it { arr }; it != arr + std::size(arr); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    // p + N steps by sizeof(int), not 1 byte.
    std::cout << "p   addr   = " << static_cast<const void*>(p)     << '\n';
    std::cout << "p+1 addr   = " << static_cast<const void*>(p + 1) << '\n';
    std::cout << "diff bytes = "
              << reinterpret_cast<const char*>(p + 1)
                 - reinterpret_cast<const char*>(p)
              << " (== sizeof(int) == " << sizeof(int) << ")\n";

    // Pointer difference gives a count, as a signed ptrdiff_t.
    int* last { arr + std::size(arr) - 1 };
    std::ptrdiff_t span { last - arr };
    std::cout << "last - arr = " << span << " elements\n";
}
