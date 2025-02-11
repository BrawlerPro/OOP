#ifndef POSITIONCOMPONENT_H
#define POSITIONCOMPONENT_H

#include <Components/BaseComponent.h>
#include <Utilities/Vector2.h>
#include <Core/GameMap.h>
#include <vector>
#include <memory>

class PositionComponent : public BaseComponent {
public:
    Vector2 position;
    std::vector<Vector2> currentPath;
    std::shared_ptr<GameMap> gameMap; // Используем умный указатель для GameMap

    PositionComponent(std::shared_ptr<Entity> e, std::shared_ptr<GameMap> gameMap, int x = 0, int y = 0);
    ~PositionComponent() override;

    void setPosition(int x, int y);
    [[nodiscard]] Vector2 getPosition() const;
    void findPath(const Vector2 &goal);
};

#endif // POSITIONCOMPONENT_H
