#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H
#include <memory>

class Entity;

class BaseComponent {
public:

    std::shared_ptr<Entity> entity;;
    explicit BaseComponent(std::shared_ptr<Entity> e = nullptr) : entity(std::move(e)) {}
    virtual ~BaseComponent() = default;

    virtual void update() {}
};
#endif // BASECOMPONENT_H
