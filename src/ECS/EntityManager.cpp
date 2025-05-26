/*
** EPITECH PROJECT, 2025
** EntityManager.cpp
** File description:
** EntityManager
*/

#include "ECS/EntityManager.hpp"

namespace ECS
{
    EntityManager::EntityManager(std::shared_ptr<ComponentManager> componentManager)
        : _componentManager(componentManager) {}

    EntityID EntityManager::createEntity()
    {
        auto entity = std::make_unique<Entity>(_componentManager);

        EntityID id = _nextEntityID++;
        entity->setID(id);
        _entities[id] = std::move(entity);
        _signatures[id] = Signature();
        return id;
    }

    void EntityManager::destroyEntity(EntityID entityID)
    {
        if (_entities.find(entityID) == _entities.end())
            return;
        _entities.erase(entityID);
        _signatures.erase(entityID);
    }

    std::vector<EntityID> EntityManager::getEntitiesWithSignature(Signature signature)
    {
        std::vector<EntityID> matchingEntities;

        for (auto &[id, entitySignature] : _signatures)
            if ((entitySignature & signature) == signature)
                matchingEntities.push_back(id);
        return matchingEntities;
    }

    Entity *EntityManager::getEntity(EntityID id) const
    {
        auto it = _entities.find(id);
        if (it != _entities.end())
            return it->second.get();
        return nullptr;
    }

        std::shared_ptr<ComponentManager> EntityManager::getComponentManager() const 
    { 
        return _componentManager; 
    };

    const std::unordered_map<EntityID, std::unique_ptr<Entity>> &EntityManager::getAllEntities() const
    {
        return _entities;
    }
}
