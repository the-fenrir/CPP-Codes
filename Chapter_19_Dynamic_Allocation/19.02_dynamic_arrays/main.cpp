// 19.2 — dynamically allocated arrays with new[] / delete[].
//
// learncpp's quiz prompt: read N names from the user, sort, print.
// We use a fixed input list instead of std::cin so `make 19.02` runs
// without blocking on stdin. The mechanics — new[], sort, delete[] —
// are identical.
//
// Modern code would write `std::vector<std::string> names = {...};`
// and skip the manual delete[] entirely.
#include <algorithm>
#include <iostream>
#include <string>

int main() {
    const std::size_t n{ 5 };

    // new T[n] — runtime-sized array on the heap. {}-init value-initializes
    // each element (default-constructed std::string for non-trivial types).
    std::string* names{ new std::string[n]{
        "charlie", "alice", "edward", "bob", "dave"
    } };

    std::cout << "before sort:\n";
    for (std::size_t i = 0; i < n; ++i) std::cout << "  " << names[i] << '\n';

    // std::sort works on any (begin, end) pointer pair. The pointer arithmetic
    // `names + n` produces a one-past-the-end pointer.
    std::sort(names, names + n);

    std::cout << "after sort:\n";
    for (std::size_t i = 0; i < n; ++i) std::cout << "  " << names[i] << '\n';

    // CRITICAL: delete[] (not delete). delete[] runs the destructor on each
    // element and frees the whole block; plain delete is UB on a new[] block.
    delete[] names;
    names = nullptr;
}
