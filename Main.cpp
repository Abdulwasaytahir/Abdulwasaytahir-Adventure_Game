#include <iostream>
#include <ctime>
#include <cstdlib>
#include "player.h"
#include "world.h"
#include "combat.h"

void displayMenu() {
    std::cout << "\n=====================================\n";
    std::cout << "     THE CHRONICLES OF C++ CORE     \n";
    std::cout << "=====================================\n";
    std::cout << " 1. New Game Adventure\n";
    std::cout << " 2. Load Existing Progress\n";
    std::cout << " 3. Show System Scoreboard Rules\n";
    std::cout << " 4. Exit Application\n";
    std::cout << "=====================================\n";
    std::cout << "Selection: ";
}

void showScoreboard() {
    std::cout << "\n=== SYSTEM SCOREBOARD CRITERIA ===\n";
    std::cout << "1. Base Level clear triggers score weights.\n";
    std::cout << "2. Completion Score Formula: Gold Balance * Level multiplier.\n";
    std::cout << "===================================\n";
}

void runGameLoop(Player& activePlayer) {
    World worldMap;
    bool processingGame = true;

    std::cout << "\nWelcome, " << activePlayer.getName() << " to the Realm!\n";
    
    while (processingGame && activePlayer.getHealth() > 0) {
        Location currentLoc = worldMap.getCurrentLocation();
        std::cout << "\n📍 Current Location: " << currentLoc.name << "\n";
        std::cout << currentLoc.description << "\n";

        worldMap.checkQuest(activePlayer);

        std::cout << "\nWhat would you like to do?\n";
        std::cout << "1. Move/Travel to another location\n";
        std::cout << "2. Inspect Character Statistics & Status\n";
        std::cout << "3. Inspect Inventory Pack\n";
        std::cout << "4. Hunt for Threats / Explore Area\n";
        std::cout << "5. Save current game progress\n";
        std::cout << "6. Give up and return to Main Menu\n";
        std::cout << "Choice: ";

        int option;
        std::cin >> option;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (option) {
            case 1: {
                std::cout << "\nWhere would you like to travel?\n";
                std::cout << "1. The Village Square\n";
                std::cout << "2. The Whispering Woods\n";
                std::cout << "3. The Forgotten Vault\n";
                std::cout << "4. The Dragon's Peak\n";
                std::cout << "Travel Target (1-4): ";
                int dest;
                std::cin >> dest;
                
                if (worldMap.moveLocation(dest, activePlayer)) {
                    // Check if they entered the Boss room
                    if (worldMap.getCurrentRoomIndex() == 3) {
                        std::cout << "\n🔥 WARNING: The ground shakes. The Dread Dragon approaches!\n";
                        Dragon boss;
                        if (CombatSystem::startEngagement(activePlayer, boss)) {
                            std::cout << "\n🏆 CONGRATULATIONS! You have slain Ignis and saved the C++ Core!\n";
                            std::cout << "Final Score: " << (activePlayer.getGold() * activePlayer.getLevel()) << "\n";
                        }
                        processingGame = false; // Game over either way
                    } else {
                        worldMap.triggerRandomEvent(activePlayer);
                    }
                }
                break;
            }
            case 2:
                activePlayer.displayStats();
                break;
            case 3:
                activePlayer.displayInventory();
                break;
            case 4: {
                if (worldMap.getCurrentRoomIndex() == 0) {
                    std::cout << "The village is completely safe. Nothing to hunt here.\n";
                } else {
                    Goblin standardMob;
                    if (!CombatSystem::startEngagement(activePlayer, standardMob)) {
                        processingGame = false; // Player died
                    }
                }
                break;
            }
            case 5:
                if (activePlayer.saveToFile("savegame.txt")) {
                    std::cout << "💾 Game successfully saved to 'savegame.txt'!\n";
                } else {
                    std::cout << "❌ Error: Could not write save file data.\n";
                }
                break;
            case 6:
                processingGame = false;
                break;
            default:
                std::cout << "Invalid system selection options.\n";
        }
    }

    if (activePlayer.getHealth() <= 0) {
        std::cout << "\n💀 GAME OVER. Your legacy ends here.\n";
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed RNG
    int choice = 0;

    while (choice != 4) {
        displayMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid system choice index structured.\n";
            continue;
        }

        if (choice == 1) {
            std::string heroicName;
            std::cout << "\nEnter your Hero's name: ";
            std::cin.ignore();
            std::getline(std::cin, heroicName);
            Player newHero(heroicName);
            runGameLoop(newHero);
        } 
        else if (choice == 2) {
            Player loadedHero;
            if (loadedHero.loadFromFile("savegame.txt")) {
                std::cout << "💾 Game loaded successfully!\n";
                runGameLoop(loadedHero);
            } else {
                std::cout << "❌ No valid save file found matching 'savegame.txt'.\n";
            }
        } 
        else if (choice == 3) {
            showScoreboard();
        }
    }

    std::cout << "\nThank you for playing the OOP Text Adventure Engine!\n";
    return 0;
}
