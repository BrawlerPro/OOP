#include <Components/AttackComponent.h>
#include <Core/Entity.h>
#include <Core/EntityManager.h>
#include <Components/OwnerComponent.h>
#include <Components/PositionComponent.h>
#include <Components/HealthComponent.h>
#include <Components/MoraleComponent.h>
#include <Components/DefenseComponent.h>
#include <Components/MovementComponent.h>
#include <Utilities/Vector2.h>
#include <cmath>
#include <limits>

using Clock = std::chrono::steady_clock;

bool isWithinRadius(const Vector2 &center, const Vector2 &point, int radius) {
    return std::sqrt(std::pow(center.x - point.x, 2) + std::pow(center.y - point.y, 2)) <= radius;
}

float calculateDistance(const Vector2 &a, const Vector2 &b) {
    return std::sqrt(static_cast<float>(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2)));
}

AttackComponent::AttackComponent(std::shared_ptr<Entity> e, int dmg, int range, float cooldown)
        : BaseComponent(std::move(e)), baseDamage(dmg), baseRange(range), attackCooldown(cooldown), lastAttackTime(0) {}

int AttackComponent::calculateDamage(const std::shared_ptr<Entity>& targetP) const {
    int damage = baseDamage;
    int range = baseRange;

    if (auto mov = entity->getComponent<MovementComponent>()) {
        damage += mov->speed;
    }

    if (auto mc = entity->getComponent<MoraleComponent>()) {
        if (auto mov = entity->getComponent<MovementComponent>()) {
            mc->adjustAttributesByMorale(damage, mov->speed, range);
        }
    }

    if (auto dc = targetP->getComponent<DefenseComponent>()) {
        damage = dc->reduceDamage(damage);
    }

    return damage;
}

void AttackComponent::attack(const std::shared_ptr<Entity>& targetP) {
    if (!targetP) return;

    auto hc = targetP->getComponent<HealthComponent>();
    if (hc && hc->isAlive()) {
        int dmg = calculateDamage(targetP);
        hc->takeDamage(dmg);

        // Если цель уничтожена
        if (!hc->isAlive()) {
            auto mc = entity->getComponent<MoraleComponent>();
            if (mc) {
                mc->increaseMorale(5);
            }

            auto ownerComp = entity->getComponent<OwnerComponent>();
            if (ownerComp) {
                // Получаем владельца
                auto summonerOwner = entity->manager.lock()->getEntity(ownerComp->ownerId);
                if (summonerOwner) { // Проверяем, что объект существует
                    auto summoner = summonerOwner->getComponent<SummonerComponent>();
                    if (summoner) {
                        summoner->gainExperience(100);
                    }
                }
            }

            // Удаление цели
            entity->manager.lock()->markForRemoval(targetP->id);
        }
    }
}


std::shared_ptr<Entity> AttackComponent::findTarget() {
    auto positionComponent = entity->getComponent<PositionComponent>();
    auto ownerComponent = entity->getComponent<OwnerComponent>();

    if (!positionComponent || !ownerComponent) return nullptr;

    Vector2 currentPosition = positionComponent->getPosition();
    std::shared_ptr<Entity> closestTarget = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (const auto& potentialTarget : entity->manager.lock()->entities) {
        if (!potentialTarget || potentialTarget == entity) continue;

        auto targetPosition = potentialTarget->getComponent<PositionComponent>();
        auto targetHealth = potentialTarget->getComponent<HealthComponent>();
        auto targetOwner = potentialTarget->getComponent<OwnerComponent>();

        if (!targetPosition || !targetHealth || !targetOwner || !targetHealth->isAlive()) continue;
        if (targetOwner->ownerId == ownerComponent->ownerId) continue;

        float distance = calculateDistance(currentPosition, targetPosition->getPosition());
        if (distance < closestDistance) {
            closestDistance = distance;
            closestTarget = potentialTarget;
        }
    }

    return closestTarget;
}

void AttackComponent::update() {
    auto now = std::chrono::duration_cast<std::chrono::seconds>(Clock::now().time_since_epoch()).count();

    target = findTarget();
    if (target.expired()) {
        return;
    }

    auto targetPtr = target.lock();
    if (!targetPtr) return;

    auto healthComp = targetPtr->getComponent<HealthComponent>();
    if (!healthComp || !healthComp->isAlive()) {
        target.reset();
        return;
    }

    auto positionComponent = entity->getComponent<PositionComponent>();
    auto movementComponent = entity->getComponent<MovementComponent>();

    if (!positionComponent) return;

    Vector2 currentPosition = positionComponent->getPosition();
    Vector2 targetPosition = targetPtr->getComponent<PositionComponent>()->getPosition();

    if (isWithinRadius(currentPosition, targetPosition, baseRange)) {
        if (static_cast<float>(now - lastAttackTime) >= attackCooldown) {
            attack(targetPtr);
            lastAttackTime = now;
        }
    } else {
        if (movementComponent) {
            movementComponent->moveTowards(targetPosition);
        }
    }
}
