/*
** EPITECH PROJECT, 2025
** Scene.hpp
** File description:
** Scene
*/

#ifndef __SCENE_H__
    #define __SCENE_H__

    #include "ECS/EntityManager.hpp"
    #include "ECS/ComponentManager.hpp"
    #include "ECS/SystemManager.hpp"
    #include "ECS/EventManager.hpp"
    #include "Engine/Types.hpp"

namespace Engine
{
    class Scene
    {
    private:
        std::shared_ptr<ECS::ComponentManager> _componentManager;
        std::shared_ptr<ECS::EntityManager> _entityManager;
        std::shared_ptr<ECS::SystemManager> _systemManager;
        std::shared_ptr<ECS::EventManager> _eventManager;

        std::shared_ptr<ECS::ComponentManager> createDefaultComponentManager();
        std::shared_ptr<ECS::EntityManager> createDefaultEntityManager(
        std::shared_ptr<ECS::ComponentManager> &componentManager);
        std::shared_ptr<ECS::SystemManager> createDefaultSystemManager();
        std::shared_ptr<ECS::EventManager> createDefaultEventManager();

        std::string _name;

    public:
        Scene(const std::string &name);
        ~Scene();

        const std::string getName() const;
        std::shared_ptr<ECS::EntityManager> getEntityManager();
        std::shared_ptr<ECS::ComponentManager> getComponentManager();
        std::shared_ptr<ECS::SystemManager> getSystemManager();
        std::shared_ptr<ECS::EventManager> getEventManager();

        void update(float deltaTime);

        std::shared_ptr<ECS::Entity> createEntity(Entity::EntityType type,
            const std::string &entityName, const Entity::EntityConfig &params = {});

        std::shared_ptr<ECS::ISystem> createSystem(System::SystemType type,
            const std::string &systemName, const System::SystemConfig &params = {});
    };
}

#endif /* !__SCENE_H__ */
