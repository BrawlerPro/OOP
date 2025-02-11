#ifndef ENERGYCOMPONENT_H
#define ENERGYCOMPONENT_H

#include <memory>
#include <Components/BaseComponent.h>

class EnergyComponent : public BaseComponent {
public:
    int maxEnergy;
    int currentEnergy;
    float accumulationRate;
    int energyCooldown;

    EnergyComponent(std::shared_ptr<Entity> e, int maxEnergy, float rate);
    void update() override;

    [[nodiscard]] bool hasEnoughEnergy(int amount) const;
    void consume(int amount);
    void accumulate();
    void setMaxEnergy(int newMax);
    void setAccumulationRate(float newRate);
};

#endif // ENERGYCOMPONENT_H
