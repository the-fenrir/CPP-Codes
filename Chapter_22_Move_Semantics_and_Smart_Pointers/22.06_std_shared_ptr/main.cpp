// 22.6 — std::shared_ptr basics + use_count trace.
//
// Also shows (commented) the classic wrong way: two shared_ptr objects
// constructed from the same raw pointer, which gives you two control blocks
// and double-deletes the resource. That bug is the topic of chapter quiz Q3.
#include <iostream>
#include <memory>

struct Resource {
    Resource()  { std::cout << "  Resource ctor\n"; }
    ~Resource() { std::cout << "  Resource dtor\n"; }
};

int main() {
    std::cout << "── make_shared + copy ──\n";
    auto p1 = std::make_shared<Resource>();
    std::cout << "  use_count after p1            = " << p1.use_count() << '\n';
    {
        auto p2 = p1;                              // refcount → 2
        std::cout << "  use_count with p2 in scope    = " << p1.use_count() << '\n';
    }                                              // p2 gone → refcount → 1
    std::cout << "  use_count after p2 scope      = " << p1.use_count() << '\n';

    std::cout << "\n── reset releases this owner's share ──\n";
    p1.reset();                                    // refcount → 0 → dtor
    std::cout << "  p1 is " << (p1 ? "non-null" : "null") << " after reset\n";

    // ── DON'T DO THIS ──────────────────────────────────────────────────
    // Resource* raw = new Resource{};
    // std::shared_ptr<Resource> bad1{ raw };
    // std::shared_ptr<Resource> bad2{ raw };
    // // bad1 and bad2 have independent control blocks → double-delete on exit.
    // // The fix: shared_ptr<Resource> bad2 = bad1; (copy from the *smart* pointer).
}
