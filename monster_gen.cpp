#include <iostream>
#include <string>
#include <random>

class Monster
{
    public:
        enum MonsterType
        {
            Dragon,
            Goblin,
            Ogre,
            Orc,
            Skeleton,
            Troll,
            Vampire,
            Zombie,
            MAX_MONSTER_TYPES
        };

    private:
        MonsterType m_type;
        std::string m_name;
        std::string m_roar;
        int m_hp;

    public:
        Monster(MonsterType type, std::string name, std::string roar, int hp) :
            m_type(type), m_name(name), m_roar(roar), m_hp(hp) {}

        std::string getTypeString(MonsterType type) {
            switch (type) {
                case Dragon:   return "dragon";
                case Goblin:   return "goblin";
                case Ogre:     return "ogre";
                case Orc:      return "orc";
                case Skeleton: return "skeleton";
                case Troll:    return "troll";
                case Vampire:  return "vampire";
                case Zombie:   return "zombie";
            }

            return "???";
        }

        void print() {
            std::cout << m_name << " the " << getTypeString(m_type) <<
                " has " << m_hp << " hit points and says " << m_roar <<
                std::endl;
        }
};

class MonsterGenerator
{
    static std::random_device rd;
    static std::mt19937_64 mersenne;

    public:
    static Monster generate()
    {
        static const int rand_max { 6 };
        static std::string s_names[rand_max] { "James", "Hunger", "Typhoon", "Alice",
            "Thor", "Ragnarok" };
        static std::string s_roars[rand_max] { "*grr*", "*ouch*", "*haha*", "*damn*",
            "*yo*", "*pika*" };

        int rand_type = mersenne() % Monster::MonsterType::MAX_MONSTER_TYPES;
        int rand_name = mersenne() % rand_max;
        int rand_roar = mersenne() % rand_max;
        int rand_hp = mersenne() % 100;

        return Monster(static_cast<Monster::MonsterType>(rand_type), s_names[rand_name],
                s_roars[rand_roar], rand_hp);
    }
};

std::random_device MonsterGenerator::rd;
std::mt19937_64 MonsterGenerator::mersenne(MonsterGenerator::rd());

int main()
{
    Monster mon = MonsterGenerator::generate();
    mon.print();

    return 0;
}
