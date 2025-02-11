#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <Core/Game.h>
#include <Core/GameMap.h>
#include <Components/PositionComponent.h>
#include <Components/HealthComponent.h>
#include <Components/AttackComponent.h>
#include <Components/SummonerComponent.h>
#include <Components/EnergyComponent.h>
#include <Components/OwnerComponent.h>
#include <TypeObjects/AbilityType.h>


bool isWithinRadius(const sf::Vector2f &center, const sf::Vector2f &point, float radius) {
    float dx = center.x - point.x;
    float dy = center.y - point.y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

Vector2 findNearestFreeCell(const Vector2 &target, const std::shared_ptr<GameMap> &gameMap) {
    const int dx[] = {-1, 1, 0, 0, -1, 1, -1, 1};
    const int dy[] = {0, 0, -1, 1, -1, 1, 1, -1};

    for (int i = 0; i < 8; ++i) {
        Vector2 neighbor(target.x + dx[i], target.y + dy[i]);
        if (gameMap->isPassable(neighbor) && !gameMap->hasEntity(neighbor)) {
            return neighbor;
        }
    }

    return {};
}

void endGame(sf::RenderWindow& window, const std::string& winnerName, sf::Font& font, unsigned int windowHeight) {
    sf::Text gameOverText("Winner: " + winnerName, font, 50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(100, windowHeight / 2 - 40);

    window.clear();
    window.draw(gameOverText);
    window.display();

    // Подождите 5 секунд, чтобы показать сообщение
    std::this_thread::sleep_for(std::chrono::seconds(5));
    window.close();
}

int main() {
    const unsigned int gridSize = 20;
    const unsigned int cellSize = 30;
    const unsigned int windowWidth = gridSize * cellSize + 250;
    const unsigned int windowHeight = gridSize * cellSize + 50;
    std::shared_ptr<AbilityType> selectedAbility = nullptr;
    int levelCost = 100;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Summoning Masters Game");
    window.setFramerateLimit(60);

    sf::RectangleShape mobSelectionRect(sf::Vector2f(200.f, windowHeight));
    mobSelectionRect.setFillColor(sf::Color(139, 69, 19));
    mobSelectionRect.setPosition(windowWidth - 200.f, 0.f);

    // Загрузка шрифта
    sf::Font font;
    if (!font.loadFromFile("./ka1.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Font font1;
    if (!font1.loadFromFile("./arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text healthText("", font, 20);
    sf::Text energyText("", font, 20);
    sf::Text schoolLevelText("", font, 20);

    healthText.setFillColor(sf::Color::White);
    energyText.setFillColor(sf::Color::White);
    schoolLevelText.setFillColor(sf::Color::White);

    healthText.setPosition(windowWidth - 190.f, windowHeight - 100.f);
    energyText.setPosition(windowWidth - 190.f, windowHeight - 70.f);
    schoolLevelText.setPosition(windowWidth - 190.f, windowHeight - 40.f);

    Game game(20, 20);
    game.loadGameFromJson("./game_data.json");
    auto entityManager = game.entityManager;
    auto gameMap = game.gameMap;

    auto summonerA = entityManager->getEntity(1);
    auto summonerB = entityManager->getEntity(2);

    auto summonSkeleton = game.abilities["skeleton"];


    std::vector<std::pair<sf::RectangleShape, std::shared_ptr<AbilityType>>> mobIcons;
    float iconStartY = 50.f;

    for (auto &[name, ability]: game.abilities) {
        sf::RectangleShape icon(sf::Vector2f(50.f, 50.f));
        icon.setFillColor(sf::Color::Black);
        icon.setPosition(windowWidth - 175.f, iconStartY);
        iconStartY += 60.f;

        mobIcons.emplace_back(icon, ability);
    }

    sf::RectangleShape levelUpButton(sf::Vector2f(150.f, 50.f));
    levelUpButton.setFillColor(sf::Color::Red);
    levelUpButton.setPosition(windowWidth - 180.f, windowHeight - 300.f);

    sf::Text levelUpText("Level UP", font, 20);
    levelUpText.setFillColor(sf::Color::Black);
    levelUpText.setPosition(levelUpButton.getPosition().x + 12, levelUpButton.getPosition().y + 12);

    sf::Text levelUpCostText("Cost: 100 XP", font, 20);
    levelUpCostText.setFillColor(sf::Color::White);
    levelUpCostText.setPosition(levelUpButton.getPosition().x, levelUpButton.getPosition().y + 55);

    sf::Text currentLevelText("Level: 1", font, 20);
    currentLevelText.setFillColor(sf::Color::White);
    currentLevelText.setPosition(levelUpButton.getPosition().x, levelUpButton.getPosition().y - 30);


    bool isSummoning = false;
    std::string winnerName = "A";
    auto gameOverTime = std::chrono::steady_clock::now();
    auto botLastSummonTime = std::chrono::steady_clock::now();
    const auto &enemySummoner = summonerB;
    const auto &currentSummoner = summonerA;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Обработка кликов по мобам
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                for (auto &[icon, ability]: mobIcons) {
                    if (icon.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                        static_cast<float>(mousePos.y))) {
                        auto requiredLevel = ability->minKnowledgeLevel;

                        if (currentSummoner->getComponent<SummonerComponent>()->level >= requiredLevel) {
                            selectedAbility = ability; // Сохраняем выбранную способность
                            isSummoning = true; // Начинаем режим призыва
                            std::cout << "Selected for summoning: " << ability->name << std::endl;
                        } else {
                            std::cout << "Insufficient level for: " << ability->name << std::endl;
                        }
                    }
                    if (isSummoning) {
                        auto summonerPos = currentSummoner->getComponent<PositionComponent>();
                        // Координаты центра призывателя в пикселях
                        sf::Vector2f summonerScreenPos(
                                summonerPos->getPosition().x * cellSize + float(cellSize) / 2,
                                summonerPos->getPosition().y * cellSize + float(cellSize) / 2
                        );
                        if (isWithinRadius(summonerScreenPos, sf::Vector2f(mousePos), 30 * 3)) {
                            auto comp = currentSummoner->getComponent<SummonerComponent>();
                            if (comp) {
                                // Преобразуем координаты мыши в координаты клетки
                                int cellX = mousePos.x / cellSize;
                                int cellY = mousePos.y / cellSize;

                                auto summonedMob = comp->summonCreature(selectedAbility);
                                if (summonedMob) {
                                    if (gameMap->cells.at(cellX, cellY)->isPassable() &&
                                        !gameMap->hasEntity({cellX, cellY})) {
                                        summonedMob->addComponent(
                                                std::make_shared<PositionComponent>(summonedMob, gameMap, cellX,
                                                                                    cellY));
                                        std::cout << "Skeleton summoned at: " << cellX << ", " << cellY << std::endl;
                                        isSummoning = false; // Завершаем процесс призыва
                                    } else {
                                        entityManager->markForRemoval(summonedMob->id);
                                    }
                                }
                            }
                        }
                    }
                }

                // Обработка клика по кнопке "Level Up"
                if (levelUpButton.getGlobalBounds().contains(static_cast<float>(mousePos.x),
                                                             static_cast<float>(mousePos.y))) {

                    if (currentSummoner->getComponent<SummonerComponent>()->experience >= levelCost) {
                        currentSummoner->getComponent<SummonerComponent>()->levelUp();
                        std::cout << "Level Up!" << std::endl;
                    } else {
                        std::cout << "Insufficient experience to level up!" << std::endl;
                    }
                }
            }
        }
        // === БОТ: Призывает скелетов каждые 5 секунд ===
        if (enemySummoner && !entityManager->isMarkedForRemoval(
                enemySummoner->id)) { // Проверяем, что enemySummoner существует и не удален
            auto now = std::chrono::steady_clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(now - botLastSummonTime).count();
            if (elapsedSeconds >= 5) {
                auto botSummoner = enemySummoner->getComponent<SummonerComponent>();
                if (botSummoner) {
                    auto enemy = botSummoner->summonCreature(summonSkeleton);
                    if (enemy) {
                        Vector2 sumPos = findNearestFreeCell(summonerB->getComponent<PositionComponent>()->position,
                                                             gameMap);
                        if (gameMap->cells.at(sumPos.x, sumPos.y)->isPassable() &&
                            !gameMap->hasEntity({sumPos.x, sumPos.y})) {
                            enemy->addComponent(
                                    std::make_shared<PositionComponent>(enemy, gameMap, sumPos.x, sumPos.y));
                            botLastSummonTime = now;
                        } else {
                            entityManager->markForRemoval(enemy->id);
                        }
                    }
                }
            }
        }
        auto summAH = summonerA->getComponent<HealthComponent>();
        auto summBH = summonerB->getComponent<HealthComponent>();

        if (!summAH || !summBH || !summAH->isAlive() || !summBH->isAlive()) {
            std::string winner = summAH && summAH->isAlive() ? "Summoner A" : "Summoner B";
            endGame(window, winner, font, windowHeight);
            break; // Завершаем главный цикл игры
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        window.clear();

        // === Отрисовка сетки и координат ===

        for (int x = 0; x < gridSize; ++x) {
            // Вертикальные линии сетки
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(x * cellSize + cellSize, cellSize), sf::Color(150, 150, 150)),
                    sf::Vertex(sf::Vector2f(x * cellSize + cellSize, gridSize * cellSize + cellSize),
                               sf::Color(150, 150, 150))
            };
            window.draw(line, 2, sf::Lines);

            // Текст координат X (сверху)
            sf::Text text(std::to_string(x + 1), font1, 14);
            text.setPosition(x * cellSize + cellSize + (cellSize / 2 - 5), 5); // Выровнять текст по центру клетки
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }

        for (int y = 0; y < gridSize; ++y) {
            // Горизонтальные линии сетки
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(cellSize, y * cellSize + cellSize), sf::Color(150, 150, 150)),
                    sf::Vertex(sf::Vector2f(gridSize * cellSize + cellSize, y * cellSize + cellSize),
                               sf::Color(150, 150, 150))
            };
            window.draw(line, 2, sf::Lines);

            // Текст координат Y (слева)
            sf::Text text(std::to_string(y + 1), font1, 14);
            text.setPosition(5, y * cellSize + cellSize + (cellSize / 2 - 7)); // Выровнять текст по центру клетки
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }

        auto summonerComponent = currentSummoner->getComponent<SummonerComponent>();
        // Обновляем и отрисовываем всех юнитов
        window.draw(mobSelectionRect);
        for (auto &[icon, ability]: mobIcons) {
            auto requiredLevel = ability->minKnowledgeLevel;
            if (summonerComponent->level >= requiredLevel) {
                icon.setFillColor(sf::Color::White);
            } else {
                icon.setFillColor(sf::Color(100, 100, 100));
            }
            window.draw(icon);
        }


        if (summonerComponent) {
            levelUpCostText.setString(
                    "Cost: " + std::to_string(SummonerComponent::requiredExperienceForLevel(summonerComponent->level)));
            currentLevelText.setString("Level: " + std::to_string(summonerComponent->level));

        }

        window.draw(levelUpCostText);
        window.draw(levelUpButton);
        window.draw(levelUpText);
        window.draw(currentLevelText);

        healthText.setString(
                "Health: " + std::to_string(currentSummoner->getComponent<HealthComponent>()->getCurrentHealth()));
        energyText.setString(
                "Energy: " + std::to_string(currentSummoner->getComponent<EnergyComponent>()->currentEnergy));
        schoolLevelText.setString(
                "Exp: " + std::to_string(currentSummoner->getComponent<SummonerComponent>()->experience));

        // Рисуем текстовые элементы
        window.draw(healthText);
        window.draw(energyText);
        window.draw(schoolLevelText);

        for (const auto &entity: entityManager->entities) {
            auto pos = entity->getComponent<PositionComponent>();
            auto own = entity->getComponent<OwnerComponent>();
            if (!pos || !own) continue;

            float px = pos->getPosition().x * cellSize;
            float py = pos->getPosition().y * cellSize;

            sf::RectangleShape shape(sf::Vector2f(cellSize, cellSize));
            if (entity->getComponent<OwnerComponent>()->name == "skeleton") {
                shape.setFillColor(sf::Color::White);
                shape.setPosition(px, py);
            } else {
                shape.setFillColor(own->ownerId == 1 ? sf::Color::Red : sf::Color::Blue);
                shape.setPosition(px, py);
            }
            window.draw(shape);
        }

        // === Отрисовка HP баров ===
        for (const auto &entity: entityManager->entities) {
            auto pos = entity->getComponent<PositionComponent>();
            auto health = entity->getComponent<HealthComponent>();
            if (!pos || !health) continue;

            float px = pos->getPosition().x * cellSize;
            float py = pos->getPosition().y * cellSize;

            // Размеры полоски HP
            float barWidth = cellSize * 0.8f;
            float barHeight = 5.f;
            float barX = px + (cellSize - barWidth) / 2; // Центрируем по X
            float barY = py - barHeight - 2; // Над мобом

            // Заполняемость HP полоски
            float hpPercentage = std::max(0.0f, (float) health->getCurrentHealth() / (float) health->getMaxHealth());
            float filledWidth = barWidth * hpPercentage;

            // Фон HP бара (чёрный)
            sf::RectangleShape hpBarBackground(sf::Vector2f(barWidth, barHeight));
            hpBarBackground.setFillColor(sf::Color::Black);
            hpBarBackground.setPosition(barX, barY);

            // Заполненная часть HP (зелёная)
            sf::RectangleShape hpBar(sf::Vector2f(filledWidth, barHeight));
            hpBar.setFillColor(sf::Color::Green);
            hpBar.setPosition(barX, barY);

            // Рисуем полоску
            window.draw(hpBarBackground);
            window.draw(hpBar);
        }

        window.display();
        game.update();

    }
    return 0;
}