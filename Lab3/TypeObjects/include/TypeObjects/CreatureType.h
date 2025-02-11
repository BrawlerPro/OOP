#ifndef CREATURETYPE_H
#define CREATURETYPE_H

#include <string>
#include <memory>

class SchoolType;

class CreatureType {
public:
    std::string name;
    std::weak_ptr<SchoolType> schoolType; // Ослабленная ссылка на школу
    bool isAmoral;
    bool isResurrectable;
    int experienceValue;
    int baseHealth;
    int baseDamage;
    int baseDefense;
    int baseSpeed;
    int baseAttackRange;

    CreatureType(std::string name, const std::shared_ptr<SchoolType>& schoolType,
                 bool isAmoral, bool isResurrectable,
                 int experienceValue,
                 int baseHealth, int baseDamage, int baseDefense,
                 int baseSpeed, int baseAttackRange)
            : name(std::move(name)),
              schoolType(std::move(schoolType)),
              isAmoral(isAmoral),
              isResurrectable(isResurrectable),
              experienceValue(experienceValue),
              baseHealth(baseHealth),
              baseDamage(baseDamage),
              baseDefense(baseDefense),
              baseSpeed(baseSpeed),
              baseAttackRange(baseAttackRange) {}
};

#endif // CREATURETYPE_H
