#ifndef MORALECOMPONENT_H
#define MORALECOMPONENT_H

#include <Components/BaseComponent.h>
#include <memory>

class MoraleComponent : public BaseComponent {
public:
    int morale;
    int moraleEffectOnDamage;
    int moraleEffectOnSpeed;
    int moraleThresholdForRangeBonus;

    MoraleComponent(std::shared_ptr<Entity> e, int initialMorale):
        BaseComponent(std::move(e)), morale(initialMorale), moraleEffectOnDamage(2), moraleEffectOnSpeed(1), moraleThresholdForRangeBonus(5) {}

    void update() override;
    void increaseMorale(int amount);
    void decreaseMorale(int amount);
    void balanceMorale();
    void adjustAttributesByMorale(int& damage, int& speed, int& attackRange) const;
    [[nodiscard]] int getMorale() const;
};

#endif // MORALECOMPONENT_H
