#include "combat.h"
#include <iostream>
#include <stdexcept>
#include <limits>

void Goblin::attack(Player& target) {
    std::cout << name << " swings a rusty dagger!\n";
    target.takeDamage(attackPower);
}

void Dragon::attack(Player& target) {
    std::cout << name << " breathes catastrophic streams of fire!\n";
    target.takeDamage(attackPower + (rand() % 10)); // Variable critical bonus
}

bool CombatSystem::startEngagement(Player& player, Enemy& enemy) {
    std::cout << "\n⚔️ COMBAT INITIATED: " << player.getName() << " VS " << enemy.getName() << " ⚔️\n";

    while (player.getHealth() > 0 && enemy.isAlive()) {
        std::cout << "\nEnemy HP: " << enemy.getHealth() << " | Your HP: " << player.getHealth() << "\n";
        std::cout << "Actions:\n1. Attack\n2. Use Potion (Heal)\nChoose action: ";
        
        int input;
        try {
            std::cin >> input;
            
            // Input Validation & Custom Exception Handling
            if(std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::invalid_argument("Input must be a valid integer code choice.");
            }
            if(input < 1 || input > 2) {
                throw std::out_of_range("Choice range out of bounds. Lose your turn concentration!");
            }
        }
        catch (const std::exception& e) {
            std::cout << "⚠️ Input Fault Exception: " << e.what() << "\n";
            input = 0; // Forfeit structural turn on error input
        }

        // Execution path
        if (input == 1) {
            int baseDamage = 15;
            if (player.hasItem("DragonSlayer Greatsword")) {
                baseDamage += 25;
                std::cout << "Your DragonSlayer Blade glows aggressively!\n";
            }
            std::cout << "You attack, dealing " << baseDamage << " damage.\n";
            enemy.takeDamage(baseDamage);
        } 
        else if (input == 2) {
            if (player.hasItem("Minor Health Potion") || player.hasItem("Elixir of Life")) {
                if (player.hasItem("Elixir of Life")) {
                    player.heal(60);
                    player.removeItem("Elixir of Life");
                } else {
                    player.heal(30);
                    player.removeItem("Minor Health Potion");
                }
            } else {
                std::cout << "You reach for potions, but your pouch is empty!\n";
            }
        }

        // Enemy Reaction Phase
        if (enemy.isAlive()) {
            enemy.attack(player);
        }
    }

    if (player.getHealth() <= 0) {
        std::cout << "\n💀 You were defeated by " << enemy.getName() << "...\n";
        return false;
    } else {
        std::cout << "\n🎉 You defeated " << enemy.getName() << "!\n";
        player.gainExperience(80);
        player.addGold(40);
        return true;
    }
}
