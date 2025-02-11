#include <Components/MovementComponent.h>
#include <Core/GameMap.h>
#include <Components/PositionComponent.h>
#include <Core/Entity.h>
#include <Components/SummonerComponent.h>
#include <iostream>

MovementComponent::MovementComponent(const std::shared_ptr<Entity> e, int speed)
        : BaseComponent(std::move(e)), speed(speed) {}

void MovementComponent::update() {
    // Можно добавить логику периодического обновления
}

void MovementComponent::moveTo(int x, int y) {
    setTarget(x, y);
}

void MovementComponent::setTarget(int x, int y) {
    moveTowards(Vector2(x, y));
}

Vector2 MovementComponent::findNearestFreeCellAround(const Vector2& target, std::shared_ptr<GameMap> gameMap) {
    if (!gameMap) return target;

    const int dx[] = {-1, 1, 0, 0, -1, 1, -1,1};
    const int dy[] = {0, 0, -1, 1, -1, 1, 1,-1};

    for (int i = 0; i < 8; ++i) {
        Vector2 neighbor(target.x + dx[i], target.y + dy[i]);
        if (gameMap->isPassable(neighbor) && !gameMap->getCell(neighbor)->hasEntity()) {
            return neighbor;
        }
    }

    return target;
}

void MovementComponent::moveTowards(const Vector2& goal) {
    auto positionComponent = entity->getComponent<PositionComponent>();
    if (!positionComponent) return;

    auto gameMap = positionComponent->gameMap;
    if (!gameMap) return;

    // Cooldown перед следующим движением
    if (moveCooldown > 0) {
        moveCooldown--;
        return;
    }

    Vector2 adjustGoal = findNearestFreeCellAround(goal, gameMap);
    if (positionComponent->currentPath.empty() || positionComponent->currentPath.back() != adjustGoal) {
        positionComponent->findPath(adjustGoal);
    }

    if (positionComponent->currentPath.empty()) {
        return;
    }

    Vector2 nextStep = positionComponent->currentPath.front();
    auto* cell = gameMap->getCell(nextStep.x, nextStep.y);
    if (cell && cell->isPassable() && !cell->hasEntity()) {
        positionComponent->setPosition(nextStep.x, nextStep.y);
        positionComponent->currentPath.erase(positionComponent->currentPath.begin());
        moveCooldown = std::max(1, 10 - speed);
    } else {
        positionComponent->findPath(adjustGoal);
    }
}
