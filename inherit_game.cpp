#include <string>
#include <iostream>

class Creature {
    protected:
        std::string m_name;
        char m_symbol;
        int m_hp;
        int m_damage;
        int m_gold;

    public:
        Creature(std::string name, char symbol, int hp, int damage, int gold) :
            m_name(name), m_symbol(symbol), m_hp(hp), m_damage(damage),
            m_gold(gold) {}

        // Getters
        std::string getName() const { return m_name; }
        char getSymbol() const { return m_symbol; }
        int getHealth() const { return m_hp; }
        int getDamage() const { return m_damage; }
        int getGold() const { return m_gold; }

        void reduceHealth(int damage) { m_hp -= damage; }
        bool isDead() const { return (m_hp <= 0); }
        void addGold(int gold) { m_gold += gold; }
};

class Player : public Creature {
    private:
        int m_level { 1 };

    public:
        Player(std::string name) : Creature(name, '@', 10, 1, 0) {}
        Player() : Player("") {}

        int getLevel() const { return m_level; }

        void levelUp() {
            ++m_level;
            ++m_damage;
        }

        bool hasWon() { return (m_level >= 20); }

        friend std::istream& operator>>(std::istream& in, Player& p) {
            std::cout << "Enter your name: ";
            in >> p.m_name;
            std::cout << "Welcome, " << p.getName() << ".\n";
            std::cout << "You have " << p.getHealth() << " health and are" <<
                " carrying " << p.getGold() << " gold." << std::endl;
        }
};

class Monster : public Creature {
    public:
        enum Type {
            DRAGON,
            ORC,
            SLIME,
            MAX_TYPES
        };

        struct Data {
            std::string name;
            char symbol;
            int hp;
            int damage;
            int gold;
        };

        static Data monsterData[MAX_TYPES]; // struct qualifier optional

        Monster(Type type) : Creature(monsterData[type].name,
                monsterData[type].symbol, monsterData[type].hp,
                monsterData[type].damage, monsterData[type].gold) {}
};

Monster::Data Monster::monsterData[Monster::MAX_TYPES] {
    { "dragon", 'D', 20, 4, 100 },
    { "orc", 'o', 4, 2, 25 },
    { "slime", 's', 1, 1, 10 }
};

int main() {
    Monster m(Monster::ORC);
    std:: cout << "A " << m.getName() << " (" << m.getSymbol() << ") was " <<
        "created." << std::endl;

    return 0;
}
