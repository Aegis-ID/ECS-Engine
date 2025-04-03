/*
** EPITECH PROJECT, 2025
** ComponentManager.hpp
** File description:
** ComponentManager
*/

#ifndef __COMPONENTMANAGER_H__
    #define __COMPONENTMANAGER_H__

    #include <cstdint>
    #include <limits>
    #include <bitset>
    #include <memory>
    #include <typeindex>
    #include <unordered_map>

    #include "IComponentPool.hpp"

namespace ECS
{
    using EntityID = uint64_t;

    using ComponentType = uint8_t;
    static const ComponentType MAX_COMPONENTS = std::numeric_limits<ComponentType>::max();
    using Signature = std::bitset<MAX_COMPONENTS>;

    class ComponentManager
    {
    private:
        ComponentType _nextType = 0;
        std::unordered_map<std::type_index, ComponentType> _typeMap;
        std::unordered_map<ComponentType, std::shared_ptr<IComponentPool>> _componentPools;
        std::unordered_map<ComponentType, std::unordered_map<EntityID, size_t>> _entityComponentMap;
    public:
        template<typename T> ComponentType registerComponent();
        template<typename T> ComponentType getComponentType();
        template<typename T> std::shared_ptr<ComponentPool<T>> getComponentPool();
        template<typename T> void setComponentOwner(std::shared_ptr<T>, EntityID);
        template<typename T> std::shared_ptr<T> getEntityComponent(EntityID);
        template<typename T> void removeEntityComponent(EntityID);
    };

    template<typename T> ComponentType ComponentManager::registerComponent()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) != _typeMap.end())
            return _typeMap.at(typeIndex);
        _typeMap[typeIndex] = _nextType;
        _componentPools[_nextType] = std::make_shared<ComponentPool<T>>();
        return _nextType++;
    }

    template<typename T> ComponentType ComponentManager::getComponentType()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) == _typeMap.end())
            throw std::runtime_error("Component not registered before use");
        return _typeMap.at(typeIndex);
    }

    template<typename T> std::shared_ptr<ComponentPool<T>> ComponentManager::getComponentPool()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) == _typeMap.end())
            throw std::runtime_error("Component type not registered");
        return std::static_pointer_cast<ComponentPool<T>>(_componentPools.at(_typeMap.at(typeIndex)));
    }

    template<typename T>
    void ComponentManager::setComponentOwner(std::shared_ptr<T> component, EntityID entityID)
    {
        if (!component)
            return;

        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) == _typeMap.end())
            throw std::runtime_error("Component type not registered");

        ComponentType typeID = _typeMap.at(typeIndex);
        auto pool = std::static_pointer_cast<ComponentPool<T>>(_componentPools.at(typeID));

        _entityComponentMap[typeID][entityID] = pool->getIndex(component);
    }

    template<typename T>
    std::shared_ptr<T> ComponentManager::getEntityComponent(EntityID entityID)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) == _typeMap.end())
            throw std::runtime_error("Component type not registered");

        ComponentType typeID = _typeMap.at(typeIndex);

        if (_entityComponentMap.find(typeID) == _entityComponentMap.end() ||
            _entityComponentMap[typeID].find(entityID) == _entityComponentMap[typeID].end())
            return nullptr;

        auto pool = std::static_pointer_cast<ComponentPool<T>>(_componentPools.at(typeID));

        return pool->getByIndex(_entityComponentMap[typeID][entityID]);
    }

    template<typename T> void ComponentManager::removeEntityComponent(EntityID entityID)
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_typeMap.find(typeIndex) == _typeMap.end())
            return;

        ComponentType typeID = _typeMap.at(typeIndex);

        if (_entityComponentMap.find(typeID) == _entityComponentMap.end() ||
            _entityComponentMap[typeID].find(entityID) == _entityComponentMap[typeID].end())
            return;

        std::size_t index = _entityComponentMap[typeID][entityID];

        _entityComponentMap[typeID].erase(entityID);
        std::static_pointer_cast<ComponentPool<T>>(_componentPools.at(typeID))->destroy(index);
    }
}

/*
 * ComponentManager is responsible for:
 * - Registering component types in the system
 * - Assigning unique IDs to each component type
 * - Creating and managing component pools for each type
 * - Tracking which entities own which components
 * - Providing efficient component access
 *
 * Usage example:
 *
 * // Create a component manager
 * ECS::ComponentManager componentManager;
 *
 * // Register component types
 * componentManager.registerComponent<PositionComponent>();
 * componentManager.registerComponent<HealthComponent>();
 *
 * // Get component type ID
 * ECS::ComponentType positionType = componentManager.getComponentType<PositionComponent>();
 *
 * // Get component pool for direct access
 * auto positionPool = componentManager.getComponentPool<PositionComponent>();
 *
 * // Get a component for a specific entity
 * auto playerPosition = componentManager.getEntityComponent<PositionComponent>(playerID);
 */

#endif /* !__COMPONENTMANAGER_H__ */
