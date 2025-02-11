#include <iostream>
#include <Core/Game.h>
#include <Components/SummonerComponent.h>
#include <Components/AttackComponent.h>
#include <Components/HealthComponent.h>
#include <Components/PositionComponent.h>
#include <Components/OwnerComponent.h>
#include <Components/EnergyComponent.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <thread>

// Конструктор
Game::Game(int width, int height) {
    entityManager = std::make_shared<EntityManager>();
    gameMap = std::make_shared<GameMap>(width, height);
}

// Обновление всех сущностей с использованием потоков
void updateEntities(const std::vector<std::shared_ptr<Entity>>& entities, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        if (auto attack = entities[i]->getComponent<AttackComponent>())
            attack->update();
        if (auto summoner = entities[i]->getComponent<SummonerComponent>())
            summoner->update();
    }
}

void Game::update() const {
    const size_t numThreads = std::thread::hardware_concurrency();
    const size_t totalEntities = entityManager->entities.size();
    const size_t chunkSize = (totalEntities + numThreads - 1) / numThreads;
    std::vector<std::thread> threads;

    for (size_t i = 0; i < numThreads; ++i) {
        size_t start = i * chunkSize;
        size_t end = std::min(start + chunkSize, totalEntities);
        threads.emplace_back(updateEntities, std::ref(entityManager->entities), start, end);
    }

    for (auto &thread: threads) {
        thread.join();
    }

    entityManager->updateAll();
}


void Game::cleanup() {
    entityManager->entities.clear();
    gameMap.reset(); // Убедитесь, что shared_ptr освобождает память
}

// Загрузка данных игры из JSON файла
void Game::loadGameFromJson(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть JSON-файл " << filename << std::endl;
        return;
    }

    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    // === 1. Загружаем школы магии ===
    for (const auto& schoolName : jsonData["schools"]) {
        schools[schoolName] = std::make_shared<SchoolType>(schoolName);
    }

    // === 2. Загружаем персонажей ===
    for (const auto& character : jsonData["characters"]) {
        std::string name = character["name"];
        std::string type = character["type"];
        int health = character.value("health", 100);
        int attack = character.value("attack", 10);
        int range = character.value("range", 2);
        int speed = character.value("speed", 0);
        int energy = character.value("energy", 0);
        int morale = character.value("morale", 0);

        if (type == "summoner") {
            int x = character["position"].value("x", 0);
            int y = character["position"].value("y", 0);

            auto entity = entityManager->createEntity();
            entity->addComponent(std::make_shared<PositionComponent>(entity, gameMap, x, y));
            entity->addComponent(std::make_shared<AttackComponent>(entity, attack, range, 2));
            entity->addComponent(std::make_shared<HealthComponent>(entity, health));
            entity->addComponent(std::make_shared<OwnerComponent>(entity, entity->id, name));
            entity->addComponent(std::make_shared<SummonerComponent>(entity, gameMap));
            entity->addComponent(std::make_shared<EnergyComponent>(entity, energy, 1));
        }

        if (type == "creature") {
            std::string school = character["school"];
            bool isAmoral = character.value("isAmoral", false);
            bool isResurrectable = character.value("isResurrectable", false);
            if (!schools.count(school)) {
                std::cerr << "Ошибка: Школа " << school << " не найдена!" << std::endl;
                continue;
            }
            creatures[name] = std::make_shared<CreatureType>(
                    name, schools[school], isAmoral, isResurrectable, morale, health, attack, 0, speed, range
            );
        }
    }

    // === 3. Загружаем способности ===
    for (const auto& ability : jsonData["abilities"]) {
        std::string schoolName = ability["school"];
        int energyCost = ability["energyCost"];
        int requireLevel = ability["requireLevel"];
        std::string summonName = ability["summoning"];

        if (!schools.count(schoolName)) {
            std::cerr << "Ошибка: Школа " << schoolName << " не найдена!" << std::endl;
            continue;
        }

        if (!creatures.count(summonName)) {
            std::cerr << "Ошибка: Существа " << summonName << " не существует!" << std::endl;
            continue;
        }

        abilities[summonName] = std::make_shared<AbilityType>(
                summonName, creatures[summonName], requireLevel, energyCost, 1.0f
        );
    }

    std::cout << "Игра успешно загружена из " << filename << std::endl;
}

// Деструктор
Game::~Game() = default;
