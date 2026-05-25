// 27.8 — three real-world pitfalls and their fixes.
#include <iostream>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// ── (a) Raw new leaks on throw; RAII does not ────────────────────────
void may_throw() { throw std::runtime_error{ "boom" }; }

void raw_new_leaks() {
    // If you uncommented this, p would leak on the throw — there's no
    // destructor to delete it during unwinding. Shown commented out so the
    // demo doesn't actually leak.
    //
    //   int* p = new int{ 42 };
    //   may_throw();
    //   delete p;   // never reached
    std::cout << "  (raw-new pattern leaks; not running it — see comment)\n";
}

void raii_is_safe() {
    auto p = std::make_unique<int>(42);  // owned by smart pointer
    try {
        may_throw();
    } catch (const std::exception& e) {
        std::cout << "  caught: " << e.what() << " — unique_ptr cleaned up automatically\n";
    }
}

// ── (b) Destructors must not throw ──────────────────────────────────
struct SafeDtor {
    ~SafeDtor() noexcept {
        // If something here could fail (file flush, network close), DO NOT
        // let the exception escape. Log it or set a flag. Throwing here
        // during stack unwinding would call std::terminate.
        std::cout << "  ~SafeDtor: swallowing any internal failure\n";
    }
};

// ── (c) Strong exception guarantee via copy-and-swap ────────────────
// append_strong either succeeds completely or leaves `v` unchanged.
void append_strong(std::vector<int>& v, int x) {
    std::vector<int> tmp = v;     // copy (may throw — original v unaffected)
    tmp.push_back(x);             // may throw — still no change to v
    v.swap(tmp);                  // noexcept — commit
}

int main() {
    std::cout << "(a) raw new vs RAII:\n";
    raw_new_leaks();
    raii_is_safe();

    std::cout << "\n(b) destructor never throws:\n";
    { SafeDtor s; (void)s; }

    std::cout << "\n(c) strong guarantee (copy-and-swap):\n";
    std::vector<int> v{ 1, 2, 3 };
    append_strong(v, 4);
    std::cout << "  v.size()=" << v.size() << ", back=" << v.back() << '\n';

    return 0;
}
