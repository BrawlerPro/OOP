#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <Components/BaseComponent.h>

class EntityManager;

class Entity : public std::enable_shared_from_this<Entity> {
public:
    int id;
    std::weak_ptr<EntityManager> manager;
    std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>> components;

    explicit Entity(int id, std::shared_ptr<EntityManager> mgr);
    ~Entity();

    template<typename T>
    std::shared_ptr<T> getComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            return std::static_pointer_cast<T>(it->second);
        }
        return nullptr;
    }

    template<typename T>
    void addComponent(std::shared_ptr<T> component) {
        if (!component) {
            throw std::invalid_argument("Error: Trying to add a null component!");
        }

        auto type = std::type_index(typeid(T));
        if (components.find(type) != components.end()) {
            std::cerr << "Warning: Component of type " << typeid(T).name() << " already exists in entity " << id << "!" << std::endl;
            return;
        }

        components[type] = component;
        component->entity = shared_from_this();
    }

    template<typename T>
    void removeComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        if (it != components.end()) {
            components.erase(it);
        }
    }

    void update();
};

#endif // ENTITY_H
