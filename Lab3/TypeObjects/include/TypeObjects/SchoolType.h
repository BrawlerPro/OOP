#ifndef SCHOOLTYPE_H
#define SCHOOLTYPE_H

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <TypeObjects/AbilityType.h>

class SchoolType {
public:
    std::string name;
    std::vector<std::shared_ptr<AbilityType>> abilities;
    std::vector<std::weak_ptr<SchoolType>> dominates; // Ослабленные ссылки на доминируемые школы

    explicit SchoolType(std::string name)
            : name(std::move(name)) {}

    void addAbility(const std::shared_ptr<AbilityType>& ability) {
        abilities.push_back(ability);
    }

    [[nodiscard]] std::shared_ptr<AbilityType> getAbilityByName(const std::string& abilityName) const {
        for (const auto& ability : abilities) {
            if (ability->name == abilityName) {
                return ability;
            }
        }
        return nullptr;
    }

    [[nodiscard]] bool dominatesSchool(const std::shared_ptr<SchoolType>& other) const {
        return std::any_of(dominates.begin(), dominates.end(), [&](const auto& dominate) {
            return dominate.lock() == other;
        });
    }
};

#endif // SCHOOLTYPE_H
