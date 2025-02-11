#ifndef GAME_H
#define GAME_H

#include <unordered_map>
#include <string>
#include <memory>
#include <Core/EntityManager.h>
#include <Core/GameMap.h>
#include <TypeObjects/SchoolType.h>
#include <TypeObjects/CreatureType.h>
#include <TypeObjects/AbilityType.h>

class Game {
public:
    std::shared_ptr<EntityManager> entityManager;
    std::shared_ptr<GameMap> gameMap;

    std::unordered_map<std::string, std::shared_ptr<SchoolType>> schools;
    std::unordered_map<std::string, std::shared_ptr<CreatureType>> creatures;
    std::unordered_map<std::string, std::shared_ptr<AbilityType>> abilities;

    Game(int width, int height);
    ~Game();
    void cleanup();
    void update() const;
    void loadGameFromJson(const std::string& filename);
};

#endif // GAME_H
