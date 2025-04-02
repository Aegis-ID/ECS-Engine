/*
** EPITECH PROJECT, 2025
** SystemManager.hpp
** File description:
** SystemManager
*/

#ifndef __SYSTEMMANAGER_H__
    #define __SYSTEMMANAGER_H__

    #include <memory>
    #include <vector>
    #include <typeindex>
    #include <unordered_map>

    #include "ISystem.hpp"

namespace ECS
{
    class SystemManager
    {
    private:
        std::vector<std::shared_ptr<ISystem>> _systems;
        std::unordered_map<std::type_index, std::shared_ptr<ISystem>> _systemMap;
    public:
        template<typename T> std::shared_ptr<T> registerSystem();
        template<typename T> std::shared_ptr<T> getSystem();
        void addSystem(std::shared_ptr<ISystem> system);
        void update(float deltaTime);
    };

    template<typename T> std::shared_ptr<T> SystemManager::registerSystem()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_systemMap.find(typeIndex) != _systemMap.end())
            return std::static_pointer_cast<T>(_systemMap[typeIndex]);
        auto system = std::make_shared<T>();
        _systems.push_back(system);
        _systemMap[typeIndex] = system;
        return system;
    }

    template<typename T> std::shared_ptr<T> SystemManager::getSystem()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_systemMap.find(typeIndex) == _systemMap.end())
            return nullptr;
        return std::static_pointer_cast<T>(_systemMap[typeIndex]);
    }
}

/*
 * SystemManager handles creation, retrieval, and updating of systems.
 * Systems are responsible for processing entities and implementing game logic.
 *
 * Key Features:
 * - Type-safe system registration and retrieval
 * - Centralized system update mechanism
 * - Support for any number of system types
 * - Efficient system lookup by type
 *
 * Usage example:
 *
 * // Create system manager
 * ECS::SystemManager systemManager;
 *
 * // Register systems
 * auto movementSystem = systemManager.registerSystem<MovementSystem>();
 * auto collisionSystem = systemManager.registerSystem<CollisionSystem>();
 *
 * // Configure systems
 * movementSystem->setEntityManager(entityManager);
 *
 * // Update all systems
 * float deltaTime = 0.016f; // ~60 FPS
 * systemManager.update(deltaTime);
 *
 * // Get a specific system
 * auto renderSystem = systemManager.getSystem<RenderSystem>();
 * if (renderSystem) {
 *     renderSystem->render();
 * }
 */

#endif /* !__SYSTEMMANAGER_H__ */
