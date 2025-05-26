/*
** EPITECH PROJECT, 2025
** Point.cpp
** File description:
** Point
** One of the only thing bethesda did right
*/

#include "include/Point.hpp"
#include "Engine/Scene.hpp"

std::string Point::getName() const
{
    return "point";
}

std::string Point::getAuthor() const
{
    return "Jiachen";
}

std::string Point::getDescription() const
{
    return "Point Plugin";
}

Engine::Version Point::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Point::getEntityType() const
{
    return Engine::Entity::EntityType::LIGHT;
}

Engine::System::SystemType Point::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

ECS::Signature Point::getEntitySignature() const
{
    return _signature;
}

bool Point::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Position>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Position>());

    return true;
}

bool Point::shutdown()
{
    return true;
}

std::vector<Engine::EntityFactoryInfo> Point::getEntityFactories()
{
    return {
    {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("Point", Engine::Entity::EntityType::LIGHT);
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::EntityInfo>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Position>(0.0f, 0.0f, 0.0f);
                auto position = entity->getComponent<Engine::CoreComponents::Position>();
                if (config.find("pos_x") != config.end())
                    position->pos_x = std::any_cast<double>(config.at("pos_x"));
                if (config.find("pos_y") != config.end())
                    position->pos_y = std::any_cast<double>(config.at("pos_y"));
                if (config.find("pos_z") != config.end())
                    position->pos_z = std::any_cast<double>(config.at("pos_z"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Position>(entity->getID());

                return entity;
            }
        }
    };
}

std::vector<Engine::SystemFactoryInfo> Point::getSystemFactories()
{
    return {};
}

void Point::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Point)
