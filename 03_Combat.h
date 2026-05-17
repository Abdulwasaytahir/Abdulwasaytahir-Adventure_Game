#ifndef COMBAT_H
#define COMBAT_H

#include <string>
#include "player.h"

// Base enemy class demonstrating Polymorphism and dynamic binding hierarchies
class Enemy {
protected:
    std::string name;
    int health;
    int attackPower;
public:
    Enemy(std::string n, int hp, int atk) : name(n), health(hp), attackPower(atk) {}
    virtual ~Enemy() {}

    std::string getName() const { return name; }
    int getHealth() const { return health; }
    bool isAlive() const { return health > 0; }

    void takeDamage(int dmg) { health -= dmg; if (health < 0) health = 0; }
    
    // Polymorphic Method
    virtual void attack(Player& target) = 0; 
};

// Derived Minor Enemy Type
class Goblin : public Enemy {
public:
    Goblin() : Enemy("Wild Goblin", 40, 10) {}
    void attack(Player& target) override;
};

// Derived Boss Enemy Type
class Dragon : public Enemy {
public:
    Dragon() : Enemy("Dread Dragon Ignis", 150, 25) {}
    void attack(Player& target) override;
};

// Orchestration engine handling execution maps
class CombatSystem {
public:
    static bool startEngagement(Player& player, Enemy& enemy);
};

#endif
