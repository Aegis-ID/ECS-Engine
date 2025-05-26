/*
** EPITECH PROJECT, 2025
** EntityManager.hpp
** File description:
** EntityManager
*/

#ifndef __ENTITYMANAGER_H__
    #define __ENTITYMANAGER_H__

    #include <unordered_map>
    #include <vector>
    #include "Entity.hpp"

namespace ECS
{
    class EntityManager
    {
    private:
        EntityID _nextEntityID = 0;
        std::unordered_map<EntityID, std::unique_ptr<Entity>> _entities;
        std::unordered_map<EntityID, Signature> _signatures;
        std::shared_ptr<ComponentManager> _componentManager;
    public:
        EntityManager(std::shared_ptr<ComponentManager> componentManager);

        EntityID createEntity();
        void destroyEntity(EntityID);

        template<typename T> void onComponentAdded(EntityID entityID);
        template<typename T> void onComponentRemoved(EntityID entityID);

        const std::unordered_map<EntityID, std::unique_ptr<Entity>> &getAllEntities() const;
        std::vector<EntityID> getEntitiesWithSignature(Signature);
        Entity *getEntity(EntityID entityID) const;

        std::shared_ptr<ComponentManager> getComponentManager() const;
    };

    template<typename T> void EntityManager::onComponentAdded(EntityID entityID)
    {
        if (_componentManager && _signatures.find(entityID) != _signatures.end())
            _signatures[entityID].set(_componentManager->getComponentType<T>(), true);
    }

    template<typename T> void EntityManager::onComponentRemoved(EntityID entityID)
    {
        if (_componentManager && _signatures.find(entityID) != _signatures.end())
            _signatures[entityID].set(_componentManager->getComponentType<T>(), false);
    }

}

#endif /* !__ENTITYMANAGER_H__ */
