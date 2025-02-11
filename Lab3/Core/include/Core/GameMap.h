#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <Utilities/Matrix.h>
#include <Core/Cell.h>
#include <Utilities/Vector2.h>
#include <memory>

class GameMap {
public:
    Matrix<std::unique_ptr<Cell>> cells;

    GameMap(int width, int height);
    ~GameMap() = default;

    [[nodiscard]] size_t getHeight() const;
    [[nodiscard]] size_t getWidth() const;
    [[nodiscard]] Cell* getCell(int x, int y) const;
    void setCell(int x, int y, std::unique_ptr<Cell> cell);
    void clearCell(const Vector2& position) const;
    [[nodiscard]] bool isPassable(const Vector2& position) const;
    [[nodiscard]] bool hasEntity(const Vector2& position) const;

    Cell* getCell(const Vector2& position) const;
    void setCell(const Vector2& position, std::unique_ptr<Cell> cell);
};

#endif // GAMEMAP_H
