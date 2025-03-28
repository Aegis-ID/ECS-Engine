/*
** EPITECH PROJECT, 2025
** Entity.cpp
** File description:
** Entity
*/

#include "../include/Entity.hpp"
#include <memory>

namespace ECS
{
    template<typename T> void Entity::addComponent()
    {
        _components[typeid(T)] = std::make_shared<ComponentWrapper<T>>;
    }

    template<typename T> void Entity::removeComponent()
    {
        _components.erase(typeid(T));
    }

    template<typename T> std::shared_ptr<T> Entity::getComponent()
    {
        auto tmp = _components.find(typeid(T));

        if (tmp != _components.end())
            return std::dynamic_pointer_cast<ComponentWrapper<T>>(tmp->second)->component;
        return nullptr;
    }
}
