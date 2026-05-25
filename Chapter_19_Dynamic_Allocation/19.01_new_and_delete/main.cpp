// 19.1 — new / delete on a single object.
//
// Demonstrates:
//   - allocation + initialization
//   - use, then delete, then nullptr the dangling pointer
//   - std::nothrow form for "don't throw, give me nullptr"
//
// Every `new` here is matched with exactly one `delete` so the program is
// leak-free under valgrind. In real code you'd reach for std::unique_ptr.
#include <iostream>
#include <new>      // std::nothrow

int main() {
    // ── plain new / delete ───────────────────────────────────────
    int* p{ new int{ 7 } };          // allocate + value-init to 7
    std::cout << "*p = " << *p << " (heap address " << p << ")\n";

    *p = 42;                          // use it like any other int
    std::cout << "*p = " << *p << '\n';

    delete p;                         // give the memory back
    p = nullptr;                      // don't leave a dangling pointer

    // delete on nullptr is a guaranteed no-op — no null check needed
    delete p;

    // ── std::nothrow form ────────────────────────────────────────
    // Normal `new` throws std::bad_alloc on failure. `new (std::nothrow)`
    // returns nullptr instead — useful if you really want to handle OOM
    // without exceptions. You MUST check the result.
    int* q{ new (std::nothrow) int{ 100 } };
    if (!q) {
        std::cerr << "allocation failed\n";
        return 1;
    }
    std::cout << "*q = " << *q << '\n';
    delete q;
    q = nullptr;
}
