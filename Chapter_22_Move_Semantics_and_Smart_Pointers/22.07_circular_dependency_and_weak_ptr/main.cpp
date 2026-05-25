// 22.7 — Cycle of shared_ptrs leaks; weak_ptr on the back-edge fixes it.
//
// Two demos in one program:
//   leakyDemo() — Person uses shared_ptr<Person> partner → no dtor prints.
//   safeDemo()  — Person uses weak_ptr<Person>  partner → dtor prints fire.
#include <iostream>
#include <memory>
#include <string>

// ── (1) Leaky version ───────────────────────────────────────────────
namespace leaky {
    struct Person {
        std::string name;
        std::shared_ptr<Person> partner;
        Person(std::string n) : name{ std::move(n) } {
            std::cout << "  ctor " << name << '\n';
        }
        ~Person() {
            std::cout << "  dtor " << name << '\n';
        }
    };
}

void leakyDemo() {
    using leaky::Person;
    std::cout << "── leaky shared_ptr cycle ──\n";
    auto lucy = std::make_shared<Person>("Lucy");
    auto ricky = std::make_shared<Person>("Ricky");
    lucy->partner  = ricky;       // refcounts: Lucy=1, Ricky=2
    ricky->partner = lucy;        // refcounts: Lucy=2, Ricky=2
    // End of scope: lucy + ricky locals destroyed → each refcount drops to 1.
    // The objects' own .partner members keep refcount at 1 forever → leak,
    // and no "dtor Lucy" / "dtor Ricky" prints.
}

// ── (2) Safe version: back-edge is weak_ptr ─────────────────────────
namespace safe {
    struct Person {
        std::string name;
        std::weak_ptr<Person> partner;     // <- the only change
        Person(std::string n) : name{ std::move(n) } {
            std::cout << "  ctor " << name << '\n';
        }
        ~Person() {
            std::cout << "  dtor " << name << '\n';
        }
        void greetPartner() const {
            if (auto p = partner.lock())   // upgrade weak → shared, check for null
                std::cout << "  " << name << " says hi to " << p->name << '\n';
            else
                std::cout << "  " << name << "'s partner is gone\n";
        }
    };
}

void safeDemo() {
    using safe::Person;
    std::cout << "── weak_ptr breaks the cycle ──\n";
    auto lucy  = std::make_shared<Person>("Lucy");
    auto ricky = std::make_shared<Person>("Ricky");
    lucy->partner  = ricky;
    ricky->partner = lucy;
    lucy->greetPartner();
    ricky->greetPartner();
    // Scope exit: refcounts drop to 0 (weak_ptrs don't hold), dtors run.
}

int main() {
    leakyDemo();
    std::cout << "  (leaky scope ended — note the missing dtors above)\n\n";
    safeDemo();
    std::cout << "  (safe scope ended — dtors ran)\n";
}
