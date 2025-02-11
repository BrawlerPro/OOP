#ifndef ABILITYTYPE_H
#define ABILITYTYPE_H

#include <string>
#include <memory>
#include <TypeObjects/CreatureType.h>

class AbilityType {
public:
    std::string name;                             // Название умения
    std::shared_ptr<CreatureType> creatureType;   // Какое существо призывается этим умением
    int minKnowledgeLevel;                        // Минимальный уровень знаний школы
    int energyCost;                               // Затраты энергии на призыв
    float quantityCoefficient;                    // Коэффициент численности от уровня знаний школы

    AbilityType(std::string name, std::shared_ptr<CreatureType> creatureType, int minKnowledgeLevel, int energyCost, float quantityCoefficient)
            : name(std::move(name)),
              creatureType(std::move(creatureType)),
              minKnowledgeLevel(minKnowledgeLevel),
              energyCost(energyCost),
              quantityCoefficient(quantityCoefficient) {}
};

#endif // ABILITYTYPE_H
