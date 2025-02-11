#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include <memory>
#include <unordered_set>
#include <mutex>
#include <Core/Entity.h>
#include <TypeObjects/CreatureType.h>

class EntityManager : public std::enable_shared_from_this<EntityManager> {
public:
    std::vector<std::shared_ptr<Entity>> entities;
    int nextEntityId;
    std::unordered_set<int> removeQueue;

    EntityManager();
    ~EntityManager();

    std::shared_ptr<Entity> createEntity();
    std::shared_ptr<Entity> createEntityFromCreatureType(const std::shared_ptr<CreatureType>& creatureType, int quantity);
    void markForRemoval(int id);
    std::shared_ptr<Entity> getEntity(int id);
    void updateAll();
    [[nodiscard]] bool isMarkedForRemoval(int id) const;

private:
    void processRemovals();
};

#endif // ENTITYMANAGER_H
