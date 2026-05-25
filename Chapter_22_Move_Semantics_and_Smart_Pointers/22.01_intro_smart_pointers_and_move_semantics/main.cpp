// 22.1 — From a leaky raw pointer to a move-only smart pointer.
//
// Three versions of the same idea, escalating:
//   (1) raw pointer    — leaks on early return.
//   (2) naive Owner    — double-frees on copy (commented out so the program runs).
//   (3) move-only Owner — copy deleted, move transfers ownership. Correct.
#include <iostream>
#include <utility>  // std::move

struct Resource {
    Resource()  { std::cout << "  Resource acquired\n"; }
    ~Resource() { std::cout << "  Resource destroyed\n"; }
};

// ── (1) Raw pointer — leaks if we return early ──────────────────────
void leaky(bool earlyReturn) {
    Resource* r = new Resource{};
    if (earlyReturn) return;       // leak
    delete r;
}

// ── (3) Move-only owner — RAII + move semantics ─────────────────────
class Owner {
    Resource* m_res{};
public:
    Owner() : m_res{ new Resource{} } {}
    ~Owner() { delete m_res; }     // safe: delete on nullptr is a no-op

    Owner(const Owner&)            = delete;   // no copies
    Owner& operator=(const Owner&) = delete;

    Owner(Owner&& other) noexcept : m_res{ other.m_res } {
        other.m_res = nullptr;     // source left empty; its dtor is now harmless
    }
    Owner& operator=(Owner&& other) noexcept {
        if (this != &other) {
            delete m_res;
            m_res = other.m_res;
            other.m_res = nullptr;
        }
        return *this;
    }
};

int main() {
    std::cout << "(1) leaky(true)  — early return, no delete runs:\n";
    leaky(true);

    std::cout << "\n(3) move-only Owner:\n";
    Owner a;                       // acquires
    Owner b{ std::move(a) };       // ownership transferred; a is now empty
    // Owner c{ b };               // would not compile: copy is deleted
    std::cout << "  (end of scope follows)\n";
}                                  // b destroys the resource exactly once
