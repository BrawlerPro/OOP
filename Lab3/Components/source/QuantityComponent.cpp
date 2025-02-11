#include <Components/QuantityComponent.h>

QuantityComponent::QuantityComponent(std::shared_ptr<Entity> e, int initialQuantity)
        : BaseComponent(std::move(e)), quantity(initialQuantity), maxQuantity(initialQuantity) {}

void QuantityComponent::increaseQuantity(int amount) {
    quantity += amount;
    if (quantity > maxQuantity) {
        quantity = maxQuantity;
    }
}

void QuantityComponent::decreaseQuantity(int amount) {
    quantity -= amount;
    if (quantity < 0) {
        quantity = 0;
    }
}

bool QuantityComponent::isEmpty() const {
    return quantity <= 0;
}

void QuantityComponent::update() {
}
