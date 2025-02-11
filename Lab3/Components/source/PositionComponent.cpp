#include <iostream>
#include <Components/PositionComponent.h>
#include <Components/OwnerComponent.h>
#include <queue>
#include <unordered_map>
#include <Core/GameMap.h>
#include <Core/EntityManager.h>
#include <Utilities/Vector2.h>
#include <algorithm>

PositionComponent::~PositionComponent() {
    if (gameMap) {
        gameMap->clearCell(position);
    }
    currentPath.clear();
}

PositionComponent::PositionComponent(std::shared_ptr<Entity> e, std::shared_ptr<GameMap> gameMap, int x, int y)
        : BaseComponent(std::move(e)), gameMap(std::move(gameMap)), position(x, y) {
    auto cell = this->gameMap->getCell(x, y);
    if (cell && cell->isPassable() && !cell->hasEntity()) {
        cell->addEntity(entity);
    } else {
        std::cerr << "Error: Cannot place entity at (" << x << ", " << y << ") - cell is not passable or already occupied." << std::endl;
    }
}

Vector2 PositionComponent::getPosition() const {
    return position;
}

void PositionComponent::setPosition(int x, int y) {
    if (x >= 0 && x < gameMap->getWidth() && y >= 0 && y < gameMap->getHeight()) {
        auto currentCell = gameMap->getCell(position.x, position.y);
        auto targetCell = gameMap->getCell(x, y);

        if (targetCell && targetCell->isPassable() && !targetCell->hasEntity()) {
            position = {x, y};
            targetCell->addEntity(entity);
            currentCell->removeEntity();
        } else {
            std::cerr << "Error: Cannot move entity to (" << x << ", " << y << ") - cell is not passable or already occupied." << std::endl;
        }
    } else {
        std::cerr << "Attempted to move out of bounds: (" << x << ", " << y << ")" << std::endl;
    }
}

void PositionComponent::findPath(const Vector2& goal) {
    if (!gameMap || !gameMap->isPassable(goal)) {
        std::cerr << "Pathfinding error: Goal (" << goal.x << ", " << goal.y << ") is occupied or not passable." << std::endl;
        return;
    }

    std::unordered_map<Vector2, Vector2> prev;
    std::unordered_map<Vector2, int> dist;

    Vector2 start = getPosition();
    std::queue<Vector2> q;

    q.push(start);
    dist[start] = 0;

    const int dx[] = {-1, 1, 0, 0, -1, -1, 1, 1}; // Влево, вправо, вверх, вниз
    const int dy[] = {0, 0, -1, 1, -1, 1, 1, -1};

    while (!q.empty()) {
        Vector2 current = q.front();
        q.pop();

        if (current == goal) {
            currentPath.clear();
            for (Vector2 at = goal; at != start; at = prev[at]) {
                currentPath.push_back(at);
            }
            std::reverse(currentPath.begin(), currentPath.end());
            return;
        }

        for (int i = 0; i < 8; ++i) { // 8 направлений движения
            Vector2 neighbor(current.x + dx[i], current.y + dy[i]);

            if (gameMap->isPassable(neighbor) && !gameMap->hasEntity(neighbor) && dist.find(neighbor) == dist.end()) {
                dist[neighbor] = dist[current] + 1;
                prev[neighbor] = current;
                q.push(neighbor);
            }
        }
    }

    std::cerr << "Path not found!" << std::endl;
    currentPath.clear();
}
