#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include <memory>
#include <Components/BaseComponent.h>

class HealthComponent : public BaseComponent {
public:
    explicit HealthComponent(std::shared_ptr<Entity> e, int maxHealth);
    void update() override;
    void takeDamage(int amount);
    void heal(int amount);

    [[nodiscard]] bool isAlive() const;
    void setMaxHealth(int newMax);

    [[nodiscard]] int getCurrentHealth() const;
    [[nodiscard]] int getMaxHealth() const;

private:
    int maxHealth;
    int currentHealth;
};

#endif // HEALTHCOMPONENT_H
