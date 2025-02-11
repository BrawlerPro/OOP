#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <Components/BaseComponent.h>
#include <Utilities/Vector2.h>
#include <vector>
#include <memory>

class GameMap;
class PositionComponent;

class MovementComponent : public BaseComponent {
public:
    explicit MovementComponent(std::shared_ptr<Entity> e, int speed);

    void update() override;
    void moveTo(int x, int y);
    void setTarget(int x, int y);
    void moveTowards(const Vector2 &goal);
    int speed;
    int moveCooldown{};
    [[nodiscard]] static Vector2 findNearestFreeCellAround(const Vector2& target, std::shared_ptr<GameMap> gameMap) ;
};

#endif // MOVEMENTCOMPONENT_H
