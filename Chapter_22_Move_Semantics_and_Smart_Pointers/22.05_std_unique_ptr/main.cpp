// 22.5 — std::unique_ptr basics: make_unique, factory by value, transfer of ownership.
#include <iostream>
#include <memory>
#include <utility>

struct Resource {
    int id;
    Resource(int i) : id{ i } { std::cout << "  Resource(" << id << ") ctor\n"; }
    ~Resource()              { std::cout << "  Resource(" << id << ") dtor\n"; }
    void use() const         { std::cout << "  using Resource(" << id << ")\n"; }
};

std::unique_ptr<Resource> make(int id) {
    return std::make_unique<Resource>(id);   // move-elided into caller
}

void consume(std::unique_ptr<Resource> r) {  // takes ownership
    r->use();
}                                            // r goes out of scope, deletes

void inspect(const Resource& r) {            // no ownership — pass by ref
    r.use();
}

int main() {
    std::cout << "── make + use ──\n";
    auto a = make(1);
    a->use();

    std::cout << "\n── pass without ownership ──\n";
    inspect(*a);

    std::cout << "\n── transfer ownership into consume() ──\n";
    consume(std::move(a));                   // a is now empty
    std::cout << "  a is " << (a ? "non-null" : "null") << " after move\n";

    // auto b = a;        // ERROR: copy is deleted.
    // auto c{ make(2) }; // would work — RVO/move

    std::cout << "\n── another scope ──\n";
    {
        auto d = make(3);
        d->use();
    }                                        // d's dtor runs here
    std::cout << "  (back in main)\n";
}
