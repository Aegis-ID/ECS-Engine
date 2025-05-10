/*
** EPITECH PROJECT, 2025
** Entity.cpp
** File description:
** Entity
*/

#include "ECS/Entity.hpp"

namespace ECS
{
    Entity::Entity(std::shared_ptr<ComponentManager> componentManager)
        : _componentManager(componentManager) {}

    void Entity::setID(EntityID id)
    {
        _id = id;
    }

    EntityID Entity::getID() const
    {
        return _id;
    }

    Signature Entity::getSignature() const
    {
        return _signature;
    }
}
