#include <Components/ResurrectionComponent.h>
#include <Components/QuantityComponent.h>
#include <Core/Entity.h>

ResurrectionComponent::ResurrectionComponent(std::shared_ptr<Entity> e, int cooldown, int countPerAttempt)
        : BaseComponent(std::move(e)), resurrectCooldown(cooldown), resurrectTimer(0), resurrectCount(countPerAttempt)
{}

void ResurrectionComponent::update() {
    if (resurrectTimer > 0) {
        resurrectTimer--;
        return;
    }

    if (canResurrect()) {
        attemptResurrect();
        resurrectTimer = resurrectCooldown;
    }
}

bool ResurrectionComponent::canResurrect() {
    auto qc = entity->getComponent<QuantityComponent>();
    if (!qc) return false;
    return (qc->quantity < qc->maxQuantity);
}

void ResurrectionComponent::attemptResurrect() {
    auto qc = entity->getComponent<QuantityComponent>();
    if (!qc) return;
    int missing = qc->maxQuantity - qc->quantity;
    if (missing <= 0) return;

    int toResurrect = (resurrectCount < missing) ? resurrectCount : missing;
    qc->increaseQuantity(toResurrect);
}
