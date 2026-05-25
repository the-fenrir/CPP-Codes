// Chapter 24 quiz solutions.
//   Q1a–e: construction/destruction order with traced ctors/dtors
//   Q2a:   Fruit ← Apple, Banana
//   Q2b:   Apple ← GrannySmith
//   Q3a–c: Creature base, Player + Monster derivations (structural pieces;
//          the full game loop is a straightforward exercise on top of these).
#include <array>
#include <iostream>
#include <string>
#include <string_view>

// ── Q1: traced hierarchy ─────────────────────────────────────────────
namespace q1 {

class Base {
public:
    int m_x{ 5 };
    Base()  { std::cout << "Base()\n"; }
    ~Base() { std::cout << "~Base()\n"; }
};

class Derived : public Base {
public:
    Derived()  { std::cout << "Derived()\n"; }
    ~Derived() { std::cout << "~Derived()\n"; }

    // Q1d/e: m_x is protected (well, public above for simplicity).
    // The point: Derived::print() can read m_x because it lives in the
    // Base subobject and is visible to derived classes.
    void print() const { std::cout << "Derived: " << m_x << '\n'; }
};

// Q1e: third level, no print() override → name lookup finds Derived::print().
class D2 : public Derived {
public:
    D2()  { std::cout << "D2()\n"; }
    ~D2() { std::cout << "~D2()\n"; }
};

void run() {
    std::cout << "-- Q1a: Derived d --\n";
    { Derived d; }

    std::cout << "\n-- Q1b: Derived d; Base b --\n";
    {
        Derived d;
        Base    b;
    }
    // Locals destroyed in reverse: ~b first, then ~d's chain.

    std::cout << "\n-- Q1d: print() with accessible m_x --\n";
    {
        Derived d;
        d.print();
    }

    std::cout << "\n-- Q1e: D2 calls inherited print() --\n";
    {
        D2 d2;
        d2.print();
    }
}

} // namespace q1

// ── Q2a/Q2b: Fruit / Apple / Banana / GrannySmith ────────────────────
//
// Design notes:
//   • `name` and `color` live in Fruit, not duplicated in derivatives.
//     Derived constructors forward the appropriate strings via the
//     initializer list (the rule from 24.4).
//   • Members are private with const accessors — encapsulation from ch.14
//     still applies; inheritance doesn't change that practice.
//   • Apple / Banana / GrannySmith add no new state, only a fixed
//     identity. That's a fine use of inheritance: a typed "preset".
namespace q2 {

class Fruit {
private:
    std::string m_name;
    std::string m_color;
public:
    Fruit(std::string name, std::string color)
        : m_name{ std::move(name) }, m_color{ std::move(color) } {}

    const std::string& getName()  const { return m_name; }
    const std::string& getColor() const { return m_color; }
};

class Apple : public Fruit {
public:
    Apple() : Fruit{ "apple", "red" } {}
protected:
    // Used by GrannySmith and anyone else who wants a renamed apple.
    Apple(std::string name, std::string color)
        : Fruit{ std::move(name), std::move(color) } {}
};

class Banana : public Fruit {
public:
    Banana() : Fruit{ "banana", "yellow" } {}
};

class GrannySmith : public Apple {
public:
    GrannySmith() : Apple{ "granny smith apple", "green" } {}
};

void describe(const Fruit& f) {
    std::cout << "My " << f.getName() << " is " << f.getColor() << ".\n";
}

void run() {
    Apple       a;
    Banana      b;
    GrannySmith g;
    describe(a);
    describe(b);
    describe(g);
}

} // namespace q2

// ── Q3a–c: Creature / Player / Monster ───────────────────────────────
//
// Design notes:
//   • Creature owns the shared state (name, symbol, health, damage, gold).
//     Player and Monster differ in *what they additionally need*, not in
//     what a "creature" is — textbook is-a.
//   • Monster::Type + a static-inline lookup table keeps construction data
//     in one spot rather than scattered across N constructors. The lookup
//     entries are themselves Creatures: each one is a fully-formed prototype.
//   • Player adds level — derived-only state — and exposes levelUp/hasWon.
//     A Monster has no concept of level, so it belongs on Player, not the base.
namespace q3 {

class Creature {
protected:
    std::string m_name;
    char        m_symbol{};
    int         m_health{};
    int         m_damage{};
    int         m_gold{};
public:
    Creature(std::string name, char symbol, int health, int damage, int gold)
        : m_name{ std::move(name) }, m_symbol{ symbol },
          m_health{ health }, m_damage{ damage }, m_gold{ gold } {}

    const std::string& getName()   const { return m_name; }
    char               getSymbol() const { return m_symbol; }
    int                getHealth() const { return m_health; }
    int                getDamage() const { return m_damage; }
    int                getGold()   const { return m_gold; }

    void reduceHealth(int n) { m_health -= n; }
    bool isDead()      const { return m_health <= 0; }
    void addGold(int n)      { m_gold += n; }
};

class Player : public Creature {
    int m_level{ 1 };
public:
    explicit Player(std::string name)
        : Creature{ std::move(name), '@', /*hp*/10, /*dmg*/1, /*gold*/0 } {}

    void levelUp()       { ++m_level; ++m_damage; }
    int  getLevel() const { return m_level; }
    bool hasWon()   const { return m_level >= 20; }
};

class Monster : public Creature {
public:
    enum Type { dragon, orc, slime, max_types };

    explicit Monster(Type type) : Creature{ prototypes()[type] } {}

private:
    static const std::array<Creature, max_types>& prototypes() {
        static const std::array<Creature, max_types> table{ {
            { "dragon", 'D', 20, 4, 100 },
            { "orc",    'o',  4, 2,  25 },
            { "slime",  's',  1, 1,  10 },
        } };
        return table;
    }
};

void run() {
    Player p{ "Player1" };
    std::cout << "Player " << p.getName() << " hp=" << p.getHealth()
              << " level=" << p.getLevel() << '\n';

    Monster d{ Monster::dragon };
    Monster o{ Monster::orc };
    Monster s{ Monster::slime };
    for (const Monster* m : { &d, &o, &s }) {
        std::cout << "  Monster " << m->getName()
                  << " [" << m->getSymbol() << "]"
                  << " hp=" << m->getHealth()
                  << " dmg=" << m->getDamage()
                  << " gold=" << m->getGold() << '\n';
    }

    // Sketch of one combat turn — full Q3f game loop is left as exercise.
    p.reduceHealth(s.getDamage());
    s.reduceHealth(p.getDamage());
    p.addGold(s.getGold());
    p.levelUp();
    std::cout << "After fighting a slime: player hp=" << p.getHealth()
              << " gold=" << p.getGold()
              << " level=" << p.getLevel() << '\n';
}

} // namespace q3

int main() {
    std::cout << "── Q1: construction/destruction order ──\n";
    q1::run();

    std::cout << "\n── Q2: Fruit / Apple / Banana / GrannySmith ──\n";
    q2::run();

    std::cout << "\n── Q3: Creature / Player / Monster ──\n";
    q3::run();
}
