#ifndef QUANTITYCOMPONENT_H
#define QUANTITYCOMPONENT_H

#include <Components/BaseComponent.h>
#include <memory>

class QuantityComponent : public BaseComponent {
public:
    int quantity;
    int maxQuantity;

    QuantityComponent(std::shared_ptr<Entity> e, int initialQuantity);
    void increaseQuantity(int amount);
    void decreaseQuantity(int amount);
    [[nodiscard]] bool isEmpty() const;
    void update() override;
};

#endif // QUANTITYCOMPONENT_H
