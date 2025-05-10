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
    #include "ComponentManager.hpp"

namespace ECS
{
    class EntityManager
    {
    private:
        EntityID _nextEntityID = 0;
        std::unordered_map<EntityID, std::shared_ptr<Entity>> _entities;
        std::unordered_map<EntityID, Signature> _signatures;
        std::shared_ptr<ComponentManager> _componentManager;
    public:
        EntityManager(std::shared_ptr<ComponentManager> componentManager);

        std::shared_ptr<Entity> createEntity();
        void destroyEntity(EntityID);

        template<typename T> void onComponentAdded(EntityID entityID);
        template<typename T> void onComponentRemoved(EntityID entityID);

        std::vector<std::shared_ptr<Entity>> getEntitiesWithSignature(Signature);
        std::shared_ptr<Entity> getEntity(EntityID entityID);

        std::shared_ptr<ComponentManager> getComponentManager() const;
    };

    template<typename T> void EntityManager::onComponentAdded(EntityID entityID)
    {
        if (_componentManager && _signatures.find(entityID) != _signatures.end()) {
            _signatures[entityID].set(_componentManager->getComponentType<T>(), true);
        }
    }

    template<typename T> void EntityManager::onComponentRemoved(EntityID entityID)
    {
        if (_componentManager && _signatures.find(entityID) != _signatures.end()) {
            _signatures[entityID].set(_componentManager->getComponentType<T>(), false);
        }
    }
}

/*
 * EntityManager is responsible for:
 * - Creating and destroying entities
 * - Tracking entity signatures for component-based filtering
 * - Providing access to entities by ID
 * - Managing entity component signatures
 *
 * Usage example:
 *
 * // Create entity manager with component manager
 * auto entityManager = std::make_shared<ECS::EntityManager>(componentManager);
 *
 * // Create a new entity
 * auto entity = entityManager->createEntity();
 *
 * // Add components and update signature
 * entity->addComponent<PositionComponent>();
 * entityManager->onComponentAdded<PositionComponent>(entity->getID());
 *
 * // Find entities with specific components
 * ECS::Signature signature;
 * signature.set(componentManager->getComponentType<PositionComponent>());
 * signature.set(componentManager->getComponentType<RenderComponent>());
 * auto renderableEntities = entityManager->getEntitiesWithSignature(signature);
 *
 * // Destroy entity when no longer needed
 * entityManager->destroyEntity(entity->getID());
 */

#endif /* !__ENTITYMANAGER_H__ */
