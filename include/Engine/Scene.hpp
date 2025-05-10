/*
** EPITECH PROJECT, 2025
** Scene.hpp
** File description:
** Scene
*/

#ifndef __SCENE_H__
    #define __SCENE_H__

    #include "../ECS/EntityManager.hpp"
    #include "../ECS/SystemManager.hpp"
    #include "../ECS/EventManager.hpp"
    #include "../ECS/ComponentManager.hpp"

namespace Engine
{
    class Scene
    {
    private:
        std::shared_ptr<ECS::ComponentManager> _componentManager;
        std::shared_ptr<ECS::EntityManager> _entityManager;
        std::shared_ptr<ECS::SystemManager> _systemManager;
        std::shared_ptr<ECS::EventManager> _eventManager;
    public:
        Scene();
        ~Scene() = default;

        void initialize();
        void load(const std::string &filename);
        void save(const std::string &filename);
        void update(float deltaTime);

        std::shared_ptr<ECS::EntityManager> getEntityManager();
        std::shared_ptr<ECS::ComponentManager> getComponentManager();
        std::shared_ptr<ECS::SystemManager> getSystemManager();
        std::shared_ptr<ECS::EventManager> getEventManager();

        // TODO: Implement factory methods for creating common entity types
        // Example :
        // std::shared_ptr<Entity> createCharacter(float x, float y);
        // std::shared_ptr<Entity> createObstacle(float x, float y, float width, float height);
        // [...]
    };
}

/*
 * Scene is a high-level container outside of the ECS, that brings together 
 * all of it's parts. It manages entities, components, and systems, and can
 * provides factory methods for creating common entity types.
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
