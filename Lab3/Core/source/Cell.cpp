#include <Core/Cell.h>

Cell::Cell(int x, int y, CellType cellType)
        : x(x), y(y), cellType(cellType) {}

bool Cell::isPassable() const {
    return cellType == CellType::Ground && entity.expired(); // Ячейка проходима, если она пустая
}

bool Cell::hasEntity() const {
    return !entity.expired(); // Проверяем, существует ли сущность
}

std::shared_ptr<Entity> Cell::getEntity() const {
    return entity.lock();
}

void Cell::addEntity(const std::shared_ptr<Entity>& e) {
    entity = e;
}

void Cell::removeEntity() {
    entity.reset();
}
