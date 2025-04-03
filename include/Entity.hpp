/*
** EPITECH PROJECT, 2025
** Entity.hpp
** File description:
** Entity
*/

#ifndef __ENTITY_H__
    #define __ENTITY_H__

    #include <cstdint>
    #include <bitset>
    #include <memory>

    #include "ComponentManager.hpp"

namespace ECS
{
    using EntityID = uint64_t;

    class Entity
    {
    private:
        EntityID _id;
        Signature _signature;
        std::shared_ptr<ComponentManager> _componentManager;
    public:
        Entity(std::shared_ptr<ComponentManager> componentManager)
            : _componentManager(componentManager) {}

        void setID(EntityID id) { _id = id; }
        EntityID getID() const { return _id; }

        Signature getSignature() const { return _signature; }

        template<typename T> void addComponent();
        template<typename T> void removeComponent();
        template<typename T> std::shared_ptr<T> getComponent();
        template<typename T> bool hasComponent() const;
    };

    template<typename T> void Entity::addComponent()
    {
        if (!_componentManager)
            return;
        _signature.set(_componentManager->getComponentType<T>());

        auto component = _componentManager->getComponentPool<T>()->create();

        _componentManager->setComponentOwner<T>(component, _id);
    }

    template<typename T> void Entity::removeComponent()
    {
        if (!_componentManager)
            return;

        ComponentType typeID = _componentManager->getComponentType<T>();

        if (!_signature[typeID])
            return;
        _signature.set(typeID, false);
        _componentManager->removeEntityComponent<T>(_id);
    }

    template<typename T> std::shared_ptr<T> Entity::getComponent()
    {
        if (!_componentManager)
            return nullptr;

        if (!_signature[_componentManager->getComponentType<T>()])
            return nullptr;
        return _componentManager->getEntityComponent<T>(_id);
    }

    template<typename T> bool Entity::hasComponent() const
    {
        if (!_componentManager)
            return false;
        return _signature[_componentManager->getComponentType<T>()];
    }
}

/*
 * Entity represents a game object in the ECS architecture.
 * Each entity is essentially an ID with a signature that indicates which components it has.
 *
 * Usage example:
 *
 * // Create an entity with a component manager
 * auto entity = std::make_shared<ECS::Entity>(componentManager);
 * entity->setID(entityID);
 *
 * // Add components
 * entity->addComponent<PositionComponent>();
 * entity->addComponent<RenderComponent>();
 *
 * // Check for a component
 * if (entity->hasComponent<CollisionComponent>()) {
 *     // Handle collision
 * }
 *
 * // Get a component
 * auto position = entity->getComponent<PositionComponent>();
 * if (position) {
 *     position->x += 10.0f;
 * }
 *
 * // Remove a component
 * entity->removeComponent<TemporaryEffectComponent>();
 */

#endif /* !__ENTITY_H__ */
