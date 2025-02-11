#ifndef SUMMONERCOMPONENT_H
#define SUMMONERCOMPONENT_H

#include <Components/BaseComponent.h>
#include <Core/GameMap.h>
#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include <Utilities/Vector2.h>

class SchoolType;
class AbilityType;
class CreatureType;
class Entity;

class SummonerComponent : public BaseComponent {
public:
    int level;
    int experience;
    int energy;
    int maxEnergy;
    std::shared_ptr<GameMap> gameMap;

    SummonerComponent(std::shared_ptr<Entity> e, std::shared_ptr<GameMap> gameMap1);
    void update() override;
    void gainExperience(int amount);
    [[nodiscard]] bool hasEnoughExperience(int required) const;
    std::shared_ptr<Entity> summonCreature(const std::shared_ptr<AbilityType>& abilityType);
    [[maybe_unused]] void levelUp();
    [[nodiscard]] bool canSummon(const std::shared_ptr<AbilityType>& abilityType) const;
    static int requiredExperienceForLevel(int targetLevel);
};

#endif // SUMMONERCOMPONENT_H
