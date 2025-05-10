/*
** EPITECH PROJECT, 2025
** Scene.cpp
** File description:
** Scene
*/

#include "Engine/Scene.hpp"

namespace Engine
{
    Scene::Scene()
    {
        _componentManager = std::make_shared<ECS::ComponentManager>();
        _entityManager = std::make_shared<ECS::EntityManager>(_componentManager);
        _systemManager = std::make_shared<ECS::SystemManager>();
        _eventManager = std::make_shared<ECS::EventManager>();
    }

    void Scene::initialize()
    {
        // Register all component types
        // Example:
        // _componentManager.registerComponent<Components::PositionComponent>();
        //
        // Register all systems
        // Example:
        // _systemManager.registerSystem<MovementSystem>();
    }

    void Scene::load(const std::string &filename)
    {
        (void)filename;
    }

    void Scene::save(const std::string &filename)
    {
        (void)filename;
    }

    void Scene::update(float deltaTime)
    {
        (void)deltaTime;
    }

    std::shared_ptr<ECS::EntityManager> Scene::getEntityManager()
    {
        return _entityManager;
    }

    std::shared_ptr<ECS::ComponentManager> Scene::getComponentManager()
    {
        return _componentManager;
    }

    std::shared_ptr<ECS::SystemManager> Scene::getSystemManager()
    {
        return _systemManager;
    }

    std::shared_ptr<ECS::EventManager> Scene::getEventManager()
    {
        return _eventManager;
    }
}
