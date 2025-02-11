#include <Components/MoraleComponent.h>

void MoraleComponent::update() {
    balanceMorale();
}

void MoraleComponent::increaseMorale(int amount) {
    morale += amount;
}

void MoraleComponent::decreaseMorale(int amount) {
    morale -= amount;
}

void MoraleComponent::balanceMorale() {
    if (morale > 0) morale--;
    else if (morale < 0) morale++;
}

void MoraleComponent::adjustAttributesByMorale(int& damage, int& speed, int& attackRange) const {
    if (morale > 0) {
        damage += morale * moraleEffectOnDamage;
        speed += morale * moraleEffectOnSpeed;
        if (morale > moraleThresholdForRangeBonus) {
            attackRange += 1;
        }
    }
    else if (morale < 0) {
        int dmgPenalty = -morale * moraleEffectOnDamage;
        damage -= dmgPenalty;
        if (damage < 1) damage = 1;

        int spdPenalty = -morale * moraleEffectOnSpeed;
        speed -= spdPenalty;
        if (speed < 1) speed = 1;

        if (morale < -moraleThresholdForRangeBonus && attackRange > 1) {
            attackRange -= 1;
        }
    }

}

int MoraleComponent::getMorale() const {
    return morale;
}
