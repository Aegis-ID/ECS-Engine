/*
** EPITECH PROJECT, 2025
** Scene.cpp
** File description:
** Scene
*/

#include "Engine/Scene.hpp"
#include "Engine/Components/EntityInfo.hpp"
#include "Engine/CoreComponents.hpp"
#include "Engine/CoreSystems.hpp"
#include "Engine/EntityType.hpp"
#include "Engine/PluginManager.hpp"
#include "Engine/SystemType.hpp"
#include "Utils/Logger.hpp"

namespace Engine
{
    Scene::Scene(const std::string &name)
    {
        auto &logger = Utils::Logger::getInstance();

        _name = name;
        logger.debug("Scene: create '%s'", name.c_str());
        _componentManager = createDefaultComponentManager();
        _entityManager = createDefaultEntityManager(_componentManager);
        _systemManager = createDefaultSystemManager();
        _eventManager = createDefaultEventManager();
    }

    Scene::~Scene()
    {
        _componentManager.reset();
        _entityManager.reset();
        _systemManager.reset();
        _eventManager.reset();
    }

    std::shared_ptr<ECS::ComponentManager> Scene::createDefaultComponentManager()
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: createDefaultComponentManager");

        std::shared_ptr<ECS::ComponentManager> defaultCM =
            std::make_shared<ECS::ComponentManager>();

        defaultCM->registerComponent<CoreComponents::EntityInfo>();
        defaultCM->registerComponent<CoreComponents::Position>();
        defaultCM->registerComponent<CoreComponents::Scale>();
        defaultCM->registerComponent<CoreComponents::Rotation>();
        defaultCM->registerComponent<CoreComponents::Color>();
        defaultCM->registerComponent<CoreComponents::Material>();
        defaultCM->registerComponent<CoreComponents::Viewport>();
        defaultCM->registerComponent<CoreComponents::Fov>();
        defaultCM->registerComponent<CoreComponents::Radius>();
        return defaultCM;
    }

    std::shared_ptr<ECS::EntityManager> Scene::createDefaultEntityManager(
        std::shared_ptr<ECS::ComponentManager> &componentManager)
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: createDefaultEntityManager");

        std::shared_ptr<ECS::EntityManager> defaultEM =
            std::make_shared<ECS::EntityManager>(componentManager);

        return defaultEM;
    }

    std::shared_ptr<ECS::SystemManager> Scene::createDefaultSystemManager()
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: createDefaultSystemManager");

        std::shared_ptr<ECS::SystemManager> defaultSM =
            std::make_shared<ECS::SystemManager>();

        return defaultSM;
    }

    std::shared_ptr<ECS::EventManager> Scene::createDefaultEventManager()
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: createDefaultEventManager");

        std::shared_ptr<ECS::EventManager> defaultEM =
            std::make_shared<ECS::EventManager>();

        return defaultEM;
    }

    const std::string Scene::getName() const
    {
        return _name;
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

    void Scene::update(float deltaTime)
    {
        _systemManager->update(deltaTime);
    }

    std::shared_ptr<ECS::Entity> Scene::createEntity(Entity::EntityType type,
        const std::string &entityName, const Entity::EntityConfig &params)
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: Creating entity %s of type %s",
            entityName.c_str(), Entity::getEntityTypeName(type));

        auto &pluginManager = PluginManager::getInstance();
        std::shared_ptr<ECS::Entity> entity =
            pluginManager.createEntity(*this, type, entityName, params);
        if (!entity)
            logger.error("Scene: Entity '%s' of type '%s' creation failed",
                entityName.c_str(), Entity::getEntityTypeName(type));
        if (!Entity::checkEntityCoreComponents(entity) || !System::checkSystemCoreComponents(entity)) {
            logger.error("Scene: Entity Factory for '%s' do not meet the required components for type '%s'",
                entityName.c_str(), Entity::getEntityTypeName(type));
            return nullptr;
        }
        return entity;
    }

    std::shared_ptr<ECS::ISystem> Scene::createSystem(System::SystemType type,
        const std::string &systemName, const System::SystemConfig &params)
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Scene: Creating system %s of type %s",
            systemName.c_str(), System::getSystemTypeName(type).c_str());

        auto &pluginManager = PluginManager::getInstance();
        auto system =
            pluginManager.createSystem(*this, type, systemName, params);
        if (!system)
            logger.error("Scene: System '%s' of type '%s' creation failed",
                systemName.c_str(), System::getSystemTypeName(type).c_str());
        return system;
    }
}
