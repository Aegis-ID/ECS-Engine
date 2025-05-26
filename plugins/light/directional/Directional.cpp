/*
** EPITECH PROJECT, 2025
** Directional.cpp
** File description:
** Directional
** One of the only thing bethesda did right
*/

#include "include/Directional.hpp"
#include "Engine/Scene.hpp"

std::string Directional::getName() const
{
    return "directional";
}

std::string Directional::getAuthor() const
{
    return "Jiachen";
}

std::string Directional::getDescription() const
{
    return "Directional Plugin";
}

Engine::Version Directional::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Directional::getEntityType() const
{
    return Engine::Entity::EntityType::LIGHT;
}

Engine::System::SystemType Directional::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

ECS::Signature Directional::getEntitySignature() const
{
    return _signature;
}

bool Directional::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Position>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Position>());
    return true;
}

bool Directional::shutdown()
{
    return true;
}

std::vector<Engine::EntityFactoryInfo> Directional::getEntityFactories()
{
    return {
    {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("directional", Engine::Entity::EntityType::LIGHT);
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

std::vector<Engine::SystemFactoryInfo> Directional::getSystemFactories()
{
    return {};
}

void Directional::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Directional)
