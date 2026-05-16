// Chapter 15 quiz — Random Monster Generator.
//
// Each section is marked `// ── X) ──` mapping back to the problem parts:
//   a) scoped MonsterType enum (then nested + unscoped inside Monster in c).
//   b) Monster class skeleton — four private members.
//   c) MonsterType moved INSIDE Monster as nested unscoped `enum Type`.
//      Callers say `Monster::Skeleton`, not `MonsterType::Skeleton`.
//   d) constructor accepting all four attributes.
//   e) getTypeString() + print() with a dead-monster branch.
//   f) MonsterGenerator namespace + generate().
//   g) getName(int) and getRoar(int) helpers in the namespace.
//   h) randomness via <random> (the site uses Random.h from lesson 8.15; we
//      inline an equivalent so the folder stays standalone).
#include <iostream>
#include <random>
#include <string>
#include <string_view>

class Monster {
public:
    // ── c) nested unscoped enum (originally MonsterType in part a) ──
    enum Type {
        Dragon,
        Goblin,
        Ogre,
        Orc,
        Skeleton,
        Troll,
        Vampire,
        Zombie,
        maxMonsterTypes,
    };

private:
    // ── b) four private members ──
    Type        m_type;
    std::string m_name;
    std::string m_roar;
    int         m_hitPoints;

public:
    // ── d) constructor ──
    Monster(Type type, std::string name, std::string roar, int hp)
        : m_type{ type }
        , m_name{ std::move(name) }
        , m_roar{ std::move(roar) }
        , m_hitPoints{ hp }
    {}

    // ── e) getTypeString() ──
    std::string_view getTypeString() const {
        switch (m_type) {
            case Dragon:   return "dragon";
            case Goblin:   return "goblin";
            case Ogre:     return "ogre";
            case Orc:      return "orc";
            case Skeleton: return "skeleton";
            case Troll:    return "troll";
            case Vampire:  return "vampire";
            case Zombie:   return "zombie";
            default:       return "???";
        }
    }

    // ── e) print() — live vs. dead ──
    void print() const {
        if (m_hitPoints <= 0) {
            std::cout << m_name << " the " << getTypeString() << " is dead.\n";
        } else {
            std::cout << m_name << " the " << getTypeString()
                      << " has " << m_hitPoints << " hit points and says "
                      << m_roar << ".\n";
        }
    }
};

// ── f) MonsterGenerator namespace ──
namespace MonsterGenerator {

    // ── h) shared RNG, seeded once. <random> equivalent of the site's Random.h. ──
    int getRandomNumber(int min, int max) {
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<int> die{ min, max };
        return die(mt);
    }

    // ── g) name / roar pools, indexed 0..5 ──
    std::string getName(int n) {
        switch (n) {
            case 0:  return "Blarg";
            case 1:  return "Moog";
            case 2:  return "Pksh";
            case 3:  return "Tyrn";
            case 4:  return "Mort";
            case 5:  return "Hans";
            default: return "???";
        }
    }
    std::string getRoar(int n) {
        switch (n) {
            case 0:  return "*ROAR*";
            case 1:  return "*hiss*";
            case 2:  return "*growl*";
            case 3:  return "*snarl*";
            case 4:  return "*screech*";
            case 5:  return "*moan*";
            default: return "???";
        }
    }

    // ── h) generate() with full randomness ──
    Monster generate() {
        auto type = static_cast<Monster::Type>(
            getRandomNumber(0, Monster::maxMonsterTypes - 1));
        return Monster{
            type,
            getName(getRandomNumber(0, 5)),
            getRoar(getRandomNumber(0, 5)),
            getRandomNumber(1, 100),
        };
    }
}

int main() {
    // Three random live monsters (hp is 1..100, always alive).
    for (int i = 0; i < 3; ++i) {
        Monster m = MonsterGenerator::generate();
        m.print();
    }

    // Force a dead monster so we always exercise the other print() branch.
    Monster dead{ Monster::Vampire, "Nibblez", "*hiss*", 0 };
    dead.print();
}
