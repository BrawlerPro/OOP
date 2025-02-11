#ifndef CELL_H
#define CELL_H

#include <Enums/CellType.h>
#include <memory>

class Entity;

class Cell {
public:
    int x;
    int y;
    CellType cellType;
    std::weak_ptr<Entity> entity;

    Cell(int x, int y, CellType cellType);
    ~Cell() = default;

    [[nodiscard]] bool isPassable() const;
    void addEntity(const std::shared_ptr<Entity>& e);
    void removeEntity();
    [[nodiscard]] bool hasEntity() const;
    [[nodiscard]] std::shared_ptr<Entity> getEntity() const;
};

#endif // CELL_H
