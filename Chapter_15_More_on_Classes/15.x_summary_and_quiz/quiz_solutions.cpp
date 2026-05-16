// Chapter 15 quiz — random monster generator.
//   a) scoped enum of monster types
//   b) Monster class with member variables
//   c) MonsterType is a nested enum inside Monster
//   d) constructor
//   e) getTypeString() and print()
//   f) MonsterGenerator namespace with generate()
//   g) name and roar helpers
//   h) random selection
#include <iostream>
#include <random>
#include <string>
#include <string_view>

class Monster {
public:
    // c) nested scoped enum
    enum class Type {
        Dragon,
        Goblin,
        Ogre,
        Orc,
        Skeleton,
        Troll,
        Vampire,
        Zombie,
        MaxMonsterTypes,
    };

private:
    Type        m_type;
    std::string m_name;
    std::string m_roar;
    int         m_hitPoints;

public:
    // d) constructor
    Monster(Type type, std::string name, std::string roar, int hp)
        : m_type{ type }
        , m_name{ std::move(name) }
        , m_roar{ std::move(roar) }
        , m_hitPoints{ hp }
    {}

    // e) human-readable type
    std::string_view getTypeString() const {
        switch (m_type) {
            case Type::Dragon:   return "dragon";
            case Type::Goblin:   return "goblin";
            case Type::Ogre:     return "ogre";
            case Type::Orc:      return "orc";
            case Type::Skeleton: return "skeleton";
            case Type::Troll:    return "troll";
            case Type::Vampire:  return "vampire";
            case Type::Zombie:   return "zombie";
            default:             return "???";
        }
    }

    // e) print
    void print() const {
        std::cout << m_name << " the " << getTypeString()
                  << " has " << m_hitPoints << " hit points and says "
                  << m_roar << '\n';
    }
};

// f) namespace for the generator
namespace MonsterGenerator {

    // g) name and roar pools
    constexpr std::string_view s_names[] = {
        "Blarg", "Moog", "Pksh", "Tyrn", "Mort", "Hans"
    };
    constexpr std::string_view s_roars[] = {
        "*ROAR*", "*hiss*", "*growl*", "*snarl*", "*screech*", "*moan*"
    };

    // Helper: random int in [min, max].
    int getRandomNumber(int min, int max) {
        static std::mt19937 mt{ std::random_device{}() };
        std::uniform_int_distribution<int> die{ min, max };
        return die(mt);
    }

    template <std::size_t N>
    std::string_view pick(const std::string_view (&arr)[N]) {
        return arr[ getRandomNumber(0, static_cast<int>(N) - 1) ];
    }

    // h) generate a random Monster
    Monster generate() {
        auto type = static_cast<Monster::Type>(
            getRandomNumber(0, static_cast<int>(Monster::Type::MaxMonsterTypes) - 1));
        return Monster{
            type,
            std::string{ pick(s_names) },
            std::string{ pick(s_roars) },
            getRandomNumber(1, 100),
        };
    }
}

int main() {
    for (int i = 0; i < 3; ++i) {
        Monster m = MonsterGenerator::generate();
        m.print();
    }
}
