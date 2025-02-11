#include <Core/Entity.h>
#include <Core/EntityManager.h>

Entity::Entity(int id, std::shared_ptr<EntityManager> mgr)
        : id(id), manager(mgr) {}

Entity::~Entity() {
    components.clear();
}

void Entity::update() {
    for (auto& pair : components) {
        pair.second->update();
    }
}

