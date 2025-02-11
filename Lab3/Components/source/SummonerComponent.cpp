#include <iostream>
#include <Components/SummonerComponent.h>
#include <Components/HealthComponent.h>
#include <Components/MovementComponent.h>
#include <Components/AttackComponent.h>
#include <Core/Entity.h>
#include <Core/EntityManager.h>
#include <TypeObjects/SchoolType.h>
#include <TypeObjects/AbilityType.h>
#include <Components/OwnerComponent.h>
#include <Components/EnergyComponent.h>
#include <Components/MoraleComponent.h>
#include <Core/GameMap.h>

SummonerComponent::SummonerComponent(std::shared_ptr<Entity> e, std::shared_ptr<GameMap> gameMap1)
        : BaseComponent(std::move(e)), gameMap(std::move(gameMap1)), level(1), experience(0), energy(0), maxEnergy(100) {}

void SummonerComponent::levelUp() {
    int requiredXP = requiredExperienceForLevel(level);
    if (experience >= requiredXP) {
        experience -= requiredXP;
        level++;
        std::cout << "Summoner leveled up to " << level << "!" << std::endl;
    } else {
        std::cout << "Not enough experience to level up!" << std::endl;
    }
}

[[maybe_unused]] bool SummonerComponent::canSummon(const std::shared_ptr<AbilityType>& abilityType) const {
    return level >= abilityType->minKnowledgeLevel && energy >= abilityType->energyCost;
}

int SummonerComponent::requiredExperienceForLevel(int targetLevel) {
    return targetLevel * 100;
}

void SummonerComponent::update() {
    auto energyComp = entity->getComponent<EnergyComponent>();
    if (energyComp) {
        energyComp->update();
    }

    auto healthComp = entity->getComponent<HealthComponent>();
    if (healthComp && !healthComp->isAlive()) {
        std::cout << "Summoner has died!" << std::endl;
    }
}

void SummonerComponent::gainExperience(int amount) {
    experience += amount;
}

bool SummonerComponent::hasEnoughExperience(int required) const {
    return experience >= required;
}

std::shared_ptr<Entity> SummonerComponent::summonCreature(const std::shared_ptr<AbilityType>& ability) {
    if (!ability) return nullptr;

    auto energyComp = entity->getComponent<EnergyComponent>();
    if (!energyComp || energyComp->currentEnergy < ability->energyCost) {
        std::cout << "Not enough energy to summon " << ability->creatureType->name << std::endl;
        return nullptr;
    }

    energyComp->consume(ability->energyCost);
    auto manager = entity->manager.lock();
    if (!manager) {
        throw std::runtime_error("Entity manager no longer exists");
    }
    auto creature = manager->createEntity();
    creature->addComponent(std::make_shared<OwnerComponent>(creature, entity->getComponent<OwnerComponent>()->ownerId, ability->creatureType->name));
    creature->addComponent(std::make_shared<HealthComponent>(creature, ability->creatureType->baseHealth));
    creature->addComponent(std::make_shared<AttackComponent>(creature, ability->creatureType->baseDamage, ability->creatureType->baseAttackRange, 2));
    creature->addComponent(std::make_shared<MovementComponent>(creature, ability->creatureType->baseSpeed));

    if (!ability->creatureType->isAmoral) {
        creature->addComponent(std::make_shared<MoraleComponent>(creature, 10));
    }

    std::cout << ability->creatureType->name << " successfully summoned!" << std::endl;
    return creature;
}
