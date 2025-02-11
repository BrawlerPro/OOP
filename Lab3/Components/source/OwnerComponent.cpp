// OwnerComponent.cpp
#include <Components/OwnerComponent.h>
#include <Core/Entity.h>
#include <Core/EntityManager.h>

bool OwnerComponent::isAlly(Entity* other) const {
    auto oc = other->getComponent<OwnerComponent>();
    if (!oc) {

        return false;
    }
    return (oc->ownerId == ownerId);
}

bool OwnerComponent::isEnemy(Entity* other) const {
    auto oc = other->getComponent<OwnerComponent>();
    if (!oc) {
        return true;
    }
    return (oc->ownerId != ownerId);
}

void OwnerComponent::setOwner(int newOwnerId) {
    ownerId = newOwnerId;
}

void OwnerComponent::update() {
}