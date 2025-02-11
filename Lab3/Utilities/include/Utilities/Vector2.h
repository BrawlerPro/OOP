#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <functional>

struct Vector2 {
    int x, y;

    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    bool operator<(const Vector2& other) const {
        return (x == other.x) ? (y < other.y) : (x < other.x);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2& vec) {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};

namespace std {
    template<>
    struct hash<Vector2> {
        size_t operator()(const Vector2& v) const {
            return hash<int>()(v.x) ^ (hash<int>()(v.y) << 1);
        }
    };
}

#endif // VECTOR2_H
