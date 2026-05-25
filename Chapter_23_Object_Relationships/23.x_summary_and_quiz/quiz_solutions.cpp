// Chapter 23 quiz — classification, demonstrated in code.
//
// For each of 1a–1f, we model the entities using storage that *expresses*
// the relationship the quiz expects. The interesting bit is the storage
// choice in each section, not the operations.
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// ── 1a — Composition: Animal owns its type + name by value ─────────────
enum class Species { dog, cat, bird };
class Animal {
    Species     m_species;
    std::string m_name;       // value member: born/dies with Animal
public:
    Animal(Species s, std::string n) : m_species{ s }, m_name{ std::move(n) } {}
    Species species() const { return m_species; }
    void greet() const {
        const char* kind = (m_species == Species::dog)  ? "dog"
                         : (m_species == Species::cat)  ? "cat"
                         : "bird";
        std::cout << "  Animal(" << m_name << ", " << kind << ")\n";
    }
};

// ── 1b — Dependency: Editor::save uses File once, doesn't store it ─────
class File {
    std::string m_path;
public:
    explicit File(std::string p) : m_path{ std::move(p) } {}
    const std::string& path() const { return m_path; }
};
class Editor {
    std::string m_text{ "hello" };
public:
    void save(File& f) const {            // parameter, not a member → dependency
        std::cout << "  save \"" << m_text << "\" → " << f.path() << '\n';
    }
};

// ── 1c — Aggregation: Adventurer holds Items by pointer; items survive ─
class Item {
    std::string m_name;
public:
    explicit Item(std::string n) : m_name{ std::move(n) } {}
    const std::string& name() const { return m_name; }
};
class Adventurer {
    std::string m_name;
    std::vector<Item*> m_inventory;       // ← pointers, not owned
public:
    explicit Adventurer(std::string n) : m_name{ std::move(n) } {}
    void pickUp(Item& it) { m_inventory.push_back(&it); }
    Item* drop()          { if (m_inventory.empty()) return nullptr;
                            Item* it = m_inventory.back();
                            m_inventory.pop_back(); return it; }
    void show() const {
        std::cout << "  " << m_name << " carries:";
        for (auto* it : m_inventory) std::cout << ' ' << it->name();
        std::cout << '\n';
    }
};

// ── 1d — Dependency: Player::pray uses a Shrine once ───────────────────
class Shrine {
    std::string m_name;
public:
    explicit Shrine(std::string n) : m_name{ std::move(n) } {}
    const std::string& name() const { return m_name; }
};
class Player {
    std::string m_name;
public:
    explicit Player(std::string n) : m_name{ std::move(n) } {}
    void prayAt(const Shrine& s) const {  // parameter only
        std::cout << "  " << m_name << " prays at " << s.name() << '\n';
    }
};

// ── 1e — Aggregation: Computer has a removable CPU ─────────────────────
class CPU {
    std::string m_model;
public:
    explicit CPU(std::string m) : m_model{ std::move(m) } {}
    const std::string& model() const { return m_model; }
};
class Computer {
    CPU* m_cpu;                           // ← removable, not owned
public:
    explicit Computer(CPU* c) : m_cpu{ c } {}
    CPU* removeCPU() { CPU* c = m_cpu; m_cpu = nullptr; return c; }
    void install(CPU* c) { m_cpu = c; }
    void show() const {
        std::cout << "  Computer with CPU: "
                  << (m_cpu ? m_cpu->model() : std::string{ "(empty)" }) << '\n';
    }
};

// ── 1f — Association: Blacksmith and his Anvil (peer-to-peer, ongoing) ─
class Anvil {
    std::string m_id;
public:
    explicit Anvil(std::string id) : m_id{ std::move(id) } {}
    const std::string& id() const { return m_id; }
};
class Blacksmith {
    std::string m_name;
    Anvil*      m_anvil;                  // long-lived ref; doesn't own
public:
    Blacksmith(std::string n, Anvil& a) : m_name{ std::move(n) }, m_anvil{ &a } {}
    void work() const {
        std::cout << "  " << m_name << " hammers on anvil " << m_anvil->id() << '\n';
    }
};

int main() {
    std::cout << "1a Composition\n";
    Animal{ Species::dog, "Rex" }.greet();

    std::cout << "1b Dependency\n";
    File f{ "/tmp/out" };
    Editor{}.save(f);

    std::cout << "1c Aggregation\n";
    Item sword{ "Sword" }, wand{ "Wand" };
    Adventurer alice{ "Alice" }, bob{ "Bob" };
    alice.pickUp(sword); alice.pickUp(wand); alice.show();
    Item* dropped = alice.drop();         // sword is shared between adventurers
    if (dropped) bob.pickUp(*dropped);
    alice.show(); bob.show();             // wand still alive, sword now Bob's

    std::cout << "1d Dependency\n";
    Shrine s{ "Shrine of Light" };
    Player{ "Hero" }.prayAt(s);

    std::cout << "1e Aggregation\n";
    CPU cpu{ "i7" };
    Computer pc{ &cpu };
    pc.show();
    CPU* yanked = pc.removeCPU();          // CPU survives outside Computer
    pc.show();
    std::cout << "  bench-testing " << yanked->model() << '\n';
    pc.install(yanked);
    pc.show();

    std::cout << "1f Association\n";
    Anvil hisAnvil{ "A-17" };
    Blacksmith{ "Gorin", hisAnvil }.work();

    // Q2: Composition. (See NOTES.md.)
}
