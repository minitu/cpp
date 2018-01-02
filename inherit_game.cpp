#include <string>
#include <iostream>
#include <random>

class Creature {
    protected:
        std::string m_name;
        char m_symbol;
        int m_hp;
        int m_max_hp;
        int m_damage;
        int m_gold;

    public:
        Creature(std::string name, char symbol, int hp, int damage, int gold) :
            m_name(name), m_symbol(symbol), m_hp(hp), m_max_hp(hp),
            m_damage(damage), m_gold(gold) {}

        // Getters
        std::string getName() const { return m_name; }
        char getSymbol() const { return m_symbol; }
        int getHealth() const { return m_hp; }
        int getMaxHealth() const { return m_max_hp; }
        int getDamage() const { return m_damage; }
        int getGold() const { return m_gold; }

        void reduceHealth(int damage) { m_hp -= damage; }
        bool isDead() const { return (m_hp <= 0); }
        void addGold(int gold) { m_gold += gold; }
};

class Monster;

class Player : public Creature {
    private:
        int m_level { 1 };

    public:
        Player(std::string name) : Creature(name, '@', 20, 1, 0) {}
        Player() : Player("") {}

        int getLevel() const { return m_level; }

        void levelUp() {
            // m_hp = m_max_hp;
            ++m_level;
            ++m_damage;
        }

        bool hasWon() { return (m_level >= 20); }

        void attack(Monster& monster);

        void gainGold(int gold) { m_gold += gold; }

        friend std::istream& operator>>(std::istream& in, Player& p) {
            std::cout << "Enter your name: ";
            in >> p.m_name;
            std::cout << "Welcome, " << p.getName() << "!\n";
        }

        void printStatus() {
            std::cout << "[Player " << m_name << "]\n" << "Level: " <<
                m_level << "\n" << "HP: " << m_hp << "/" << m_max_hp << "\n" <<
                "Gold: " << m_gold << std::endl;
        }
};

class Monster : public Creature {
    private:
        static std::random_device rd;
        static std::mt19937_64 mersenne;

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

        static Monster getRandomMonster() {
            int random = mersenne() % 10;
            Type random_type;
            if (random == 0) random_type = DRAGON;
            else if (random > 0 && random < 5) random_type = ORC;
            else random_type = SLIME;

            return Monster(random_type);
        }

        void attack(Player& player) {
            player.reduceHealth(m_damage);
            std::cout << "The " << m_name << " hit you for " << m_damage <<
                " damage.\n";
            std::cout << "Your health: " << player.getHealth() << "/" <<
                player.getMaxHealth() << std::endl;
        }
};

void Player::attack(Monster& monster) {
    monster.reduceHealth(m_damage);
    std::cout << "You hit the " << monster.getName() <<
        " for " << m_damage << " damage.\n";
    std::cout << "Monster's health: " << monster.getHealth() << "/" <<
        monster.getMaxHealth() << std::endl;
}

Monster::Data Monster::monsterData[Monster::MAX_TYPES] {
    { "dragon", 'D', 20, 4, 100 },
    { "orc", 'o', 4, 2, 25 },
    { "slime", 's', 1, 1, 10 }
};

std::random_device Monster::rd;
std::mt19937_64 Monster::mersenne(Monster::rd());

enum class EncounterResult {
    NEXT_MONSTER,
    PLAYER_DEAD
};

EncounterResult encounter(Player& player, Monster& monster) {
    // Random number generator setup for fleeing
    static std::random_device rd;
    static std::mt19937_64 mersenne(rd());

    // Keep fighting until one is dead or player flees
    while (!monster.isDead() && !player.isDead()) {
        // Run or fight?
        std::string decision;
        std::cout << "\n(R)un or (F)ight? " << std::endl;
        std::cin >> decision;
        std::locale loc;
        for (std::string::size_type i = 0; i < decision.length(); ++i) {
            decision[i] = std::tolower(decision[i], loc); // Make lowercase
        }

        // Handle player's decision
        if (decision == "r") { // RUN!
            int random = mersenne() % 2; // 50% chance of fleeing
            if (random == 0) { // Flee success! Return to live another day
                std::cout << "You successfully fled." << std::endl;
                return EncounterResult::NEXT_MONSTER;
            }
            else { // Failed to flee
                std::cout << "You failed to flee." << std::endl;
                monster.attack(player);
            }
        }
        else {
            // Player gets to attack the monster first
            player.attack(monster);

            if (monster.isDead()) {
                // Killed monster: loot gold and level up
                player.gainGold(monster.getGold());
                player.levelUp();

                std::cout << "You have killed a " << monster.getName() <<
                    " and gained " << monster.getGold() << " gold!\n" <<
                    std::endl;

                player.printStatus();
            }
            else {
                // Monster attacks back
                monster.attack(player);
            }
        }
    }

    return (player.isDead() ? EncounterResult::PLAYER_DEAD :
            EncounterResult::NEXT_MONSTER);
}

int main() {
    // Player setup
    Player player;
    std::cin >> player;

    // Main game loop
    while (true) {
        // Generate random monster and encounter
        Monster monster = Monster::getRandomMonster();
        std::cout << "\nYou have encountered a " << monster.getName() << " (" <<
            monster.getSymbol() << ")." << std::endl;
        EncounterResult result = encounter(player, monster);

        // Check encounter result
        if (result == EncounterResult::PLAYER_DEAD) {
            std::cout << "Too bad, you have died..." << std::endl;
            player.printStatus();
            break;
        }
        else if (result == EncounterResult::NEXT_MONSTER) {
            // Break out of loop if player has won
            if (player.hasWon()) {
                std::cout << "\nCongratulations! You have won the game!\n\n";
                player.printStatus();
                break;
            }
        }
    }

    return 0;
}
