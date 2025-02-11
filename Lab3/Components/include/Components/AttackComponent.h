#ifndef ATTACKCOMPONENT_H
#define ATTACKCOMPONENT_H

#include <memory>
#include <vector>
#include <chrono>
#include <Components/BaseComponent.h>
#include <Utilities/Vector2.h>

class Entity;

class AttackComponent : public BaseComponent {
public:
    int baseDamage;
    int baseRange;
    float attackCooldown;
    long lastAttackTime;

    AttackComponent(std::shared_ptr<Entity> e, int damage, int range, float cooldown);

    void update() override;

    void attack(const std::shared_ptr<Entity>& target);
    [[nodiscard]] int calculateDamage(const std::shared_ptr<Entity>& target) const;

private:
    std::weak_ptr<Entity> target;
    std::shared_ptr<Entity> findTarget();
};

#endif // ATTACKCOMPONENT_H
