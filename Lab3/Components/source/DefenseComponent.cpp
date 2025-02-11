#include <Components/DefenseComponent.h>
#include <memory>

DefenseComponent::DefenseComponent(std::shared_ptr<Entity> e, int defenseValue)
        : BaseComponent(std::move(e)), defenseValue(defenseValue) {}

int DefenseComponent::reduceDamage(int incoming) const {
    int reduced = incoming - defenseValue;
    if (reduced < 0) reduced = 0;
    return reduced;
}
