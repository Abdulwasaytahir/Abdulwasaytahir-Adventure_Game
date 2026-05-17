#ifndef WORLD_H
#define WORLD_H

#include <string>
#include <vector>
#include "player.h"

// Abstract Base Class modeling design patterns (Abstraction)
class GameEntity {
protected:
    std::string name;
public:
    GameEntity(std::string n) : name(n) {}
    virtual ~GameEntity() {}
    virtual std::string getName() const = 0; // Pure Virtual Function
};

struct Location {
    std::string name;
    std::string description;
    bool isLocked;
    std::string keyRequired;
};

class World {
private:
    std::vector<Location> map;
    int currentRoomIndex;
    bool questCompleted;

public:
    World();
    void initializeWorld();
    Location getCurrentLocation() const;
    int getCurrentRoomIndex() const;
    
    // Core structural functions
    bool moveLocation(int choice, Player& player);
    void triggerRandomEvent(Player& player);
    void checkQuest(Player& player);
    bool isGameWon() const;
};

#endif
