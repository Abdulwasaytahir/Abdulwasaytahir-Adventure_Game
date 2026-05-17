#include "player.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Player::Player() : name("Unknown"), health(100), maxHealth(100), level(1), experience(0), gold(50) {
    inventory.push_back("Rusty Sword");
    inventory.push_back("Minor Health Potion");
}

Player::Player(std::string name) : name(name), health(100), maxHealth(100), level(1), experience(0), gold(50) {
    inventory.push_back("Rusty Sword");
    inventory.push_back("Minor Health Potion");
}

Player::~Player() {
    // Destructor implementation - free dynamic resources if expanded later
}

std::string Player::getName() const { return name; }
int Player::getHealth() const { return health; }
int Player::getMaxHealth() const { return maxHealth; }
int Player::getLevel() const { return level; }
int Player::getGold() const { return gold; }
std::vector<std::string> Player::getInventory() const { return inventory; }

void Player::setHealth(int hp) { 
    health = std::min(hp, maxHealth); 
    if (health < 0) health = 0;
}

void Player::addGold(int amount) { gold += amount; }

bool Player::removeGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }
    return false;
}

void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
    std::cout << name << " takes " << damage << " damage! Current HP: " << health << "/" << maxHealth << "\n";
}

void Player::heal(int amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
    std::cout << name << " heals for " << amount << " HP! Current HP: " << health << "/" << maxHealth << "\n";
}

void Player::gainExperience(int exp) {
    experience += exp;
    std::cout << "Gained " << exp << " EXP points.\n";
    int expNeeded = level * 100;
    if (experience >= expNeeded) {
        experience -= expNeeded;
        level++;
        maxHealth += 20;
        health = maxHealth;
        std::cout << "✨ LEVEL UP! You reached Level " << level << "! Max HP increased to " << maxHealth << ".\n";
    }
}

void Player::addItem(const std::string& item) {
    inventory.push_back(item);
    std::cout << item << " added to your inventory!\n";
}

bool Player::hasItem(const std::string& item) const {
    return std::find(inventory.begin(), inventory.end(), item) != inventory.end();
}

void Player::removeItem(const std::string& item) {
    auto it = std::find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end()) {
        inventory.erase(it);
    }
}

void Player::displayStats() const {
    std::cout << "\n===============================\n";
    std::cout << "       CHARACTER STATS        \n";
    std::cout << "===============================\n";
    std::cout << " Name:       " << name << "\n";
    std::cout << " Level:      " << level << "\n";
    std::cout << " HP:         " << health << " / " << maxHealth << "\n";
    std::cout << " Experience: " << experience << " / " << (level * 100) << "\n";
    std::cout << " Gold:       " << gold << "g\n";
    std::cout << "===============================\n";
}

void Player::displayInventory() const {
    std::cout << "\n--- Your Inventory ---\n";
    if (inventory.empty()) {
        std::cout << "[Empty]\n";
        return;
    }
    for (size_t i = 0; i < inventory.size(); ++i) {
        std::cout << i + 1 << ". " << inventory[i] << "\n";
    }
}

bool Player::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) return false;

    outFile << name << "\n" << health << "\n" << maxHealth << "\n" 
            << level << "\n" << experience << "\n" << gold << "\n";
    
    outFile << inventory.size() << "\n";
    for (const auto& item : inventory) {
        outFile << item << "\n";
    }
    return true;
}

bool Player::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) return false;

    std::getline(inFile, name);
    inFile >> health >> maxHealth >> level >> experience >> gold;
    
    size_t invSize;
    inFile >> invSize;
    inFile.ignore(); // clear newline character

    inventory.clear();
    for (size_t i = 0; i < invSize; ++i) {
        std::string item;
        std::getline(inFile, item);
        inventory.push_back(item);
    }
    return true;
}
