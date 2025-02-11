#ifndef OWNERCOMPONENT_H
#define OWNERCOMPONENT_H

#include <Components/BaseComponent.h>
#include <Components/SummonerComponent.h>
#include <Core/Entity.h>

class OwnerComponent : public BaseComponent {
public:
    int ownerId;
    std::string name;

    OwnerComponent(std::shared_ptr<Entity> e, int ownerId, std::string name)
            : BaseComponent(std::move(e)), ownerId(ownerId), name(std::move(name)) {}
    void update() override;
    bool isAlly(Entity* other) const;
    bool isEnemy(Entity* other) const;
    void setOwner(int newOwnerId);
};

#endif // OWNERCOMPONENT_H
