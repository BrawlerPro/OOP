#include <Core/EntityManager.h>
#include <algorithm>
#include <Components/PositionComponent.h>
#include <Components/OwnerComponent.h>
#include <Components/HealthComponent.h>
#include <Components/AttackComponent.h>

EntityManager::EntityManager() : nextEntityId(1) {}

EntityManager::~EntityManager() {
    entities.clear(); // `std::shared_ptr` очистит память автоматически
}

std::shared_ptr<Entity> EntityManager::createEntity() {
    auto entity = std::make_shared<Entity>(nextEntityId++, shared_from_this());
    entities.push_back(entity);
    return entity;
}

void EntityManager::markForRemoval(int id) {
    removeQueue.insert(id);
}

void EntityManager::updateAll() {
    processRemovals();
}



void EntityManager::processRemovals() {
    entities.erase(
            std::remove_if(entities.begin(), entities.end(),
                           [&](const std::shared_ptr<Entity>& entity) {
                               if (removeQueue.count(entity->id)) {
                                   auto positionComponent = entity->getComponent<PositionComponent>();
                                   if (positionComponent) {
                                       positionComponent->gameMap->clearCell(positionComponent->getPosition());
                                   }
                                   return true; // Удаляем объект из вектора
                               }
                               return false;
                           }),
            entities.end()
    );
    removeQueue.clear();
}

std::shared_ptr<Entity> EntityManager::getEntity(int id) {
    for (auto& entity : entities) {
        if (entity->id == id) return entity;
    }
    return nullptr;
}

bool EntityManager::isMarkedForRemoval(int id) const {
    return removeQueue.find(id) != removeQueue.end();
}

std::shared_ptr<Entity> EntityManager::createEntityFromCreatureType(const std::shared_ptr<CreatureType>& type, int quantity) {
    if (!type) return nullptr;

    auto newEntity = createEntity();
    newEntity->addComponent(std::make_shared<HealthComponent>(newEntity, type->baseHealth * quantity));
    newEntity->addComponent(std::make_shared<AttackComponent>(newEntity, type->baseDamage, 1, 1));

    return newEntity;
}
