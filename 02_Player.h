#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

class Player {
private:
    std::string name;
    int health;
    int maxHealth;
    int level;
    int experience;
    int gold;
    std::vector<std::string> inventory;

public:
    // Constructors and Destructor
    Player();
    Player(std::string name);
    ~Player();

    // Getters and Setters (Encapsulation)
    std::string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getLevel() const;
    int getGold() const;
    std::vector<std::string> getInventory() const;

    void setHealth(int hp);
    void addGold(int amount);
    bool removeGold(int amount);

    // Business Logic Methods
    void takeDamage(int damage);
    void heal(int amount);
    void gainExperience(int exp);
    void addItem(const std::string& item);
    bool hasItem(const std::string& item) const;
    void removeItem(const std::string& item);
    void displayStats() const;
    void displayInventory() const;

    // File Handling
    bool saveToFile(const std::string& filename) const;
    bool loadFromFile(const std::string& filename);
};

#endif
