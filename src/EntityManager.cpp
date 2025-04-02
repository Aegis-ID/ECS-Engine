/*
** EPITECH PROJECT, 2025
** EntityManager.cpp
** File description:
** EntityManager
*/

#include "../include/EntityManager.hpp"

namespace ECS
{
    std::shared_ptr<Entity> EntityManager::createEntity()
    {
        auto entity = std::make_shared<Entity>(_componentManager);

        entity->setID(_nextEntityID);
        _entities[_nextEntityID] = entity;
        _signatures[_nextEntityID] = Signature();
        _nextEntityID++;
        return entity;
    }

    void EntityManager::destroyEntity(EntityID entityID)
    {
        if (_entities.find(entityID) == _entities.end())
            return;
        _entities.erase(entityID);
        _signatures.erase(entityID);
    }

    std::vector<std::shared_ptr<Entity>> EntityManager::getEntitiesWithSignature(Signature signature)
    {
        std::vector<std::shared_ptr<Entity>> matchingEntities;

        for (auto &[id, entitySignature] : _signatures)
            if ((entitySignature & signature) == signature)
                matchingEntities.push_back(_entities[id]);
        return matchingEntities;
    }

    std::shared_ptr<Entity> EntityManager::getEntity(EntityID entityID)
    {
        if (_entities.find(entityID) == _entities.end())
            return nullptr;
        return _entities[entityID];
    }
}
