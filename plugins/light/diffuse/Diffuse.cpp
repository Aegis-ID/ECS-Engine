/*
** EPITECH PROJECT, 2025
** Diffuse.cpp
** File description:
** Diffuse
** One of the only thing bethesda did right
*/

#include "include/Diffuse.hpp"

std::string Diffuse::getName() const
{
    return "diffuse";
}

std::string Diffuse::getAuthor() const
{
    return "Jiachen";
}

std::string Diffuse::getDescription() const
{
    return "Diffuse Plugin";
}

Engine::Version Diffuse::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Diffuse::getEntityType() const
{
    return Engine::Entity::EntityType::LIGHT;
}

Engine::System::SystemType Diffuse::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

bool Diffuse::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Scale>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Scale>());

    return true;
}

bool Diffuse::shutdown()
{
    return true;
}

ECS::Signature Diffuse::getEntitySignature() const
{
    return _signature;
}

std::vector<Engine::EntityFactoryInfo> Diffuse::getEntityFactories()
{
    return {
    {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("diffuse", Engine::Entity::EntityType::LIGHT);
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

std::vector<Engine::SystemFactoryInfo> Diffuse::getSystemFactories()
{
    return {};
}

void Diffuse::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Diffuse)
