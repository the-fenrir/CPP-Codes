// Chapter 22 quiz solutions.
//   Q1: discussion — see NOTES.md
//   Q2: discussion — see NOTES.md
//   Q3: fix the broken double-shared_ptr-from-raw-pointer code.
//
// We don't even define the buggy version in code, since it has undefined
// behavior — we just describe it in NOTES.md and demonstrate the fix here.
#include <iostream>
#include <memory>

class Resource {
public:
    Resource()  { std::cout << "  Resource acquired\n"; }
    ~Resource() { std::cout << "  Resource destroyed\n"; }
};

int main() {
    std::cout << "── Q3 fix: make_shared + copy from the smart pointer ──\n";
    auto ptr1{ std::make_shared<Resource>() };
    std::cout << "  use_count after ptr1                  = " << ptr1.use_count() << '\n';
    {
        auto ptr2{ ptr1 };                              // shares ptr1's control block
        std::cout << "  use_count with ptr2 in scope          = " << ptr1.use_count() << '\n';
    }                                                   // ptr2 gone → refcount → 1
    std::cout << "  use_count after ptr2 scope            = " << ptr1.use_count() << '\n';
    // ptr1 leaves main → refcount → 0 → Resource destroyed exactly once.
}
