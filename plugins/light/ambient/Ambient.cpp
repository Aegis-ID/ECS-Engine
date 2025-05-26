/*
** EPITECH PROJECT, 2025
** Ambient.cpp
** File description:
** Ambient
** One of the only thing bethesda did right
*/

#include "include/Ambient.hpp"
#include "Engine/Components/EntityInfo.hpp"
#include "Engine/Core.hpp"
#include "Engine/Scene.hpp"

std::string Ambient::getName() const
{
    return "ambient";
}

std::string Ambient::getAuthor() const
{
    return "Jiachen";
}

std::string Ambient::getDescription() const
{
    return "Ambient Plugin";
}

Engine::Version Ambient::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Ambient::getEntityType() const
{
    return Engine::Entity::EntityType::LIGHT;
}

Engine::System::SystemType Ambient::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

ECS::Signature Ambient::getEntitySignature() const
{
    return _signature;
}

bool Ambient::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Scale>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Scale>());

    return true;
}

bool Ambient::shutdown()
{
    return true;
}

std::vector<Engine::EntityFactoryInfo> Ambient::getEntityFactories()
{
    return {
    {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("ambient", Engine::Entity::EntityType::LIGHT);
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::EntityInfo>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Scale>(0.0f);
                auto scale = entity->getComponent<Engine::CoreComponents::Scale>();
                if (config.find("scale") != config.end())
                    scale->scale = std::any_cast<double>(config.at("scale"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Scale>(entity->getID());

                return entity;
            }
        }
    };
}

std::vector<Engine::SystemFactoryInfo> Ambient::getSystemFactories()
{
    return {};
}

void Ambient::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Ambient)
