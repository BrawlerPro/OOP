#include <Components/HealthComponent.h>
#include <iostream>

HealthComponent::HealthComponent(std::shared_ptr<Entity> e, int maxHealth)
        : BaseComponent(std::move(e)), maxHealth(maxHealth), currentHealth(maxHealth) {
    if (maxHealth <= 0) {
        std::cerr << "Error: maxHealth must be greater than zero!" << std::endl;
        this->maxHealth = 1; // Минимальное значение здоровья
        this->currentHealth = 1;
    }
}

void HealthComponent::update() {
    // В будущем можно добавить логику регенерации или эффектов
}

void HealthComponent::takeDamage(int amount) {
    if (amount < 0) {
        std::cerr << "Error: takeDamage received a negative value!" << std::endl;
        return;
    }

    currentHealth -= amount;
    if (currentHealth < 0) currentHealth = 0;
}

void HealthComponent::heal(int amount) {
    if (amount < 0) {
        std::cerr << "Error: heal received a negative value!" << std::endl;
        return;
    }

    currentHealth += amount;
    if (currentHealth > maxHealth) currentHealth = maxHealth;
}

bool HealthComponent::isAlive() const {
    return currentHealth > 0;
}

void HealthComponent::setMaxHealth(int newMax) {
    if (newMax <= 0) {
        std::cerr << "Error: maxHealth must be greater than zero!" << std::endl;
        return;
    }

    maxHealth = newMax;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

int HealthComponent::getCurrentHealth() const {
    return currentHealth;
}

int HealthComponent::getMaxHealth() const {
    return maxHealth;
}
