// DefenseComponent.h
#ifndef DEFENSECOMPONENT_H
#define DEFENSECOMPONENT_H


#include <memory>
#include <Components/BaseComponent.h>

class DefenseComponent : public BaseComponent {
public:
    int defenseValue{};

    DefenseComponent(std::shared_ptr<Entity> e, int defenseValue);
    [[nodiscard]] int reduceDamage(int incoming) const;
    void update() override {}
};

#endif // DEFENSECOMPONENT_H
