/*
** EPITECH PROJECT, 2025
** Scene.hpp
** File description:
** Scene
*/

#ifndef __SCENE_H__
    #define __SCENE_H__

    #include "EntityManager.hpp"
    #include "SystemManager.hpp"
    #include "EventManager.hpp"
    #include "ComponentManager.hpp"

// This is a scene implementation example

namespace ECS
{
    class Scene
    {
    private:
        std::shared_ptr<ComponentManager> _componentManager;
        std::shared_ptr<EntityManager> _entityManager;
        std::shared_ptr<SystemManager> _systemManager;
        std::shared_ptr<EventManager> _eventManager;
    public:
        Scene()
        {
            _componentManager = std::make_shared<ComponentManager>();
            _entityManager = std::make_shared<EntityManager>(_componentManager);
            _systemManager = std::make_shared<SystemManager>();
            _eventManager = std::make_shared<EventManager>();
        }

        void initialize();
        // Register all component types
        // Example:
        // _componentManager.registerComponent<Components::PositionComponent>();
        //
        // Register all systems
        // Example:
        // _systemManager.registerSystem<MovementSystem>();

        void load(const std::string &filename);
        void save(const std::string &filename);
        void update(float deltaTime);

        std::shared_ptr<EntityManager> getEntityManager() { return _entityManager; }
        std::shared_ptr<ComponentManager> getComponentManager() { return _componentManager; }
        std::shared_ptr<SystemManager> getSystemManager() { return _systemManager; }
        std::shared_ptr<EventManager> getEventManager() { return _eventManager; }

        // TODO: Implement factory methods for creating common entity types
        // Example :
        // std::shared_ptr<Entity> createCharacter(float x, float y);
        // std::shared_ptr<Entity> createObstacle(float x, float y, float width, float height);
        // [...]
    };
}

/*
 * Scene is a high-level container that brings together all parts of the ECS.
 * It manages entities, components, and systems, and provides factory methods
 * for creating common entity types.
 *
 * Usage example:
 *
 * // Create a scene
 * ECS::Scene scene;
 * scene.initialize();
 *
 * // Create entities
 * auto player = scene.createCharacter(100.0f, 100.0f);
 * auto obstacle = scene.createObstacle(200.0f, 200.0f, 50.0f, 50.0f);
 *
 * // Add custom components
 * player->addComponent<WeaponComponent>();
 * scene.getEntityManager().onComponentAdded<WeaponComponent>(player->getID());
 *
 * // Create a custom system
 * auto collisionSystem = scene.getSystemManager().registerSystem<CollisionSystem>();
 * collisionSystem->setEntityManager(scene.getEntityManager());
 *
 * // Game loop
 * float deltaTime = 0.016f;
 * while (gameRunning) {
 *     scene.update(deltaTime);
 *     // Render
 * }
 *
 * // Save scene state
 * scene.save("savegame.qqch");
 */

#endif /* !__SCENE_H__ */
