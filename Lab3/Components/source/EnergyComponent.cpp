#include <Components/EnergyComponent.h>
#include <iostream>

EnergyComponent::EnergyComponent(std::shared_ptr<Entity> e, int maxEnergy, float rate)
        : BaseComponent(std::move(e)), maxEnergy(maxEnergy), currentEnergy(maxEnergy), accumulationRate(rate), energyCooldown(0) {}

void EnergyComponent::update() {
    if (energyCooldown > 0) {
        energyCooldown--;
        return;
    }

    if (currentEnergy < maxEnergy) {
        accumulate();
        energyCooldown = 30; // Устанавливаем кулдаун для предотвращения быстрого накопления
    }
}

bool EnergyComponent::hasEnoughEnergy(int amount) const {
    return currentEnergy >= amount;
}

void EnergyComponent::consume(int amount) {
    if (amount < 0) {
        std::cerr << "Error: Trying to consume negative energy!" << std::endl;
        return;
    }

    currentEnergy -= amount;
    if (currentEnergy < 0) {
        currentEnergy = 0;
    }
}

void EnergyComponent::accumulate() {
    if (accumulationRate < 0) {
        std::cerr << "Error: Negative accumulation rate!" << std::endl;
        return;
    }

    currentEnergy += static_cast<int>(accumulationRate);
    if (currentEnergy > maxEnergy) {
        currentEnergy = maxEnergy;
    }
}

void EnergyComponent::setMaxEnergy(int newMax) {
    if (newMax < 0) {
        std::cerr << "Error: Negative max energy!" << std::endl;
        return;
    }

    maxEnergy = newMax;
    if (currentEnergy > maxEnergy) {
        currentEnergy = maxEnergy;
    }
}

void EnergyComponent::setAccumulationRate(float newRate) {
    if (newRate < 0) {
        std::cerr << "Error: Negative accumulation rate!" << std::endl;
        return;
    }

    accumulationRate = newRate;
}
