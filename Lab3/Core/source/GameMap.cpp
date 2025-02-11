#include <Core/GameMap.h>

GameMap::GameMap(int width, int height)
        : cells(width, height) {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            cells[x][y] = std::make_unique<Cell>(x, y, CellType::Ground);
        }
    }
}


size_t GameMap::getHeight() const {
    return cells.getColCount();
}

size_t GameMap::getWidth() const {
    return cells.getRowCount();
}

Cell* GameMap::getCell(int x, int y) const {
    if (x < 0 || x >= cells.getRowCount() || y < 0 || y >= cells.getColCount()) {
        return nullptr;
    }
    return cells[x][y].get();
}

Cell* GameMap::getCell(const Vector2& position) const {
    return getCell(position.x, position.y);
}

void GameMap::setCell(int x, int y, std::unique_ptr<Cell> cell) {
    if (x >= 0 && x < getWidth() && y >= 0 && y < getHeight()) {
        cells[x][y] = std::move(cell);
    } else {
        std::cerr << "Error: Attempt to set a cell out of bounds at (" << x << ", " << y << ")" << std::endl;
    }
}

void GameMap::setCell(const Vector2& position, std::unique_ptr<Cell> cell) {
    setCell(position.x, position.y, std::move(cell));
}

void GameMap::clearCell(const Vector2& position) const {
    auto* cell = getCell(position.x, position.y);
    if (cell) {
        cell->removeEntity();
    }
}

bool GameMap::isPassable(const Vector2& position) const {
    Cell* cell = getCell(position.x, position.y);
    return cell && cell->isPassable();
}

bool GameMap::hasEntity(const Vector2& position) const {
    if (auto* cell = getCell(position)) {
        return cell->hasEntity();
    }
    return false;
}
