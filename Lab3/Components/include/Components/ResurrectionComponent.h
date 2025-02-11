#ifndef RESURRECTIONCOMPONENT_H
#define RESURRECTIONCOMPONENT_H

#include <Components/BaseComponent.h>
#include <Components/QuantityComponent.h>

class ResurrectionComponent : public BaseComponent {
public:
    int resurrectCooldown;
    int resurrectTimer;
    int resurrectCount;

    ResurrectionComponent(std::shared_ptr<Entity> e, int cooldown, int countPerAttempt);
    void update() override;

private:
    void attemptResurrect();
    bool canResurrect() ;
};

#endif // RESURRECTIONCOMPONENT_H
