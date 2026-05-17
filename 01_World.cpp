#include "world.h"
#include <iostream>
#include <cstdlib>

World::World() : currentRoomIndex(0), questCompleted(false) {
    initializeWorld();
}

void World::initializeWorld() {
    map.push_back({"The Village Square", "A quiet starting town. Safe but full of whispers about danger.", false, ""});
    map.push_back({"The Whispering Woods", "Thick tree lines full of dangerous beasts.", false, ""});
    map.push_back({"The Forgotten Vault", "An old stone crypt. It looks like it requires a Citadel Key.", true, "Citadel Key"});
    map.push_back({"The Dragon's Peak", "The volatile home of the Dread Dragon Ignis.", false, ""});
}

Location World::getCurrentLocation() const {
    return map[currentRoomIndex];
}

int World::getCurrentRoomIndex() const {
    return currentRoomIndex;
}

bool World::moveLocation(int choice, Player& player) {
    if (choice < 1 || choice > static_cast<int>(map.size())) {
        std::cout << "Invalid destination selection.\n";
        return false;
    }

    int targetIndex = choice - 1;

    // Check if location restriction systems apply
    if (map[targetIndex].isLocked) {
        if (player.hasItem(map[targetIndex].keyRequired)) {
            std::cout << "🔓 You unlock " << map[targetIndex].name << " using your " << map[targetIndex].keyRequired << "!\n";
            map[targetIndex].isLocked = false; 
        } else {
            std::cout << "🔒 " << map[targetIndex].name << " is locked! You need a " << map[targetIndex].keyRequired << ".\n";
            return false;
        }
    }

    currentRoomIndex = targetIndex;
    return true;
}

void World::triggerRandomEvent(Player& player) {
    int eventChance = rand() % 3; // 0, 1, or 2

    if (currentRoomIndex == 0) return; // Village remains completely secure

    std::cout << "\n--- Area Exploration Event ---\n";
    if (eventChance == 0) {
        std::cout << "You uncovered an old treasure cache concealed in the brush!\n";
        player.addGold(30);
        std::cout << "Found 30 gold coins.\n";
    } else if (eventChance == 1) {
        std::cout << "You tripped a hidden dart floor trap left by primitive tribes!\n";
        player.takeDamage(15);
    } else {
        std::cout << "The path is quiet, keeping you on edge but unharmed.\n";
    }
}

void World::checkQuest(Player& player) {
    if (currentRoomIndex == 1 && !player.hasItem("Citadel Key") && !questCompleted) {
        std::cout << "\n📜 [QUEST TRIGGERED] You met a dying knight in the woods.\n";
        std::cout << "Knight: 'Take this key... stop the beast at the Dragon's Peak...'\n";
        player.addItem("Citadel Key");
    }
    
    if (currentRoomIndex == 2 && player.hasItem("Citadel Key") && !questCompleted) {
        std::cout << "\n📜 [QUEST LOG] You've infiltrated the Vault. Inside a chest you secure an 'Elixir of Life' and a 'DragonSlayer Greatsword'!\n";
        player.addItem("Elixir of Life");
        player.addItem("DragonSlayer Greatsword");
        player.gainExperience(150);
        questCompleted = true;
    }
}

bool World::isGameWon() const {
    return currentRoomIndex == 3 && questCompleted; 
}
