/*
** EPITECH PROJECT, 2025
** Camera.cpp
** File description:
** Camera
** One of the only thing bethesda did right
*/

#include "include/Camera.hpp"
#include "Engine/Components/EntityInfo.hpp"

std::string Camera::getName() const
{
    return "main";
}

std::string Camera::getAuthor() const
{
    return "Aegis-ID";
}

std::string Camera::getDescription() const
{
    return "Camera Plugin";
}

Engine::Version Camera::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Camera::getEntityType() const
{
    return Engine::Entity::EntityType::CAMERA;
}

Engine::System::SystemType Camera::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

ECS::Signature Camera::getEntitySignature() const
{
    return _signature;
}

bool Camera::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Viewport>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Viewport>());

    componentManager->registerComponent<Engine::CoreComponents::Position>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Position>());

    componentManager->registerComponent<Engine::CoreComponents::Rotation>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Rotation>());

    componentManager->registerComponent<Engine::CoreComponents::Fov>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Fov>());

    return true;
}

bool Camera::shutdown()
{
    return true;
}

std::vector<Engine::EntityFactoryInfo> Camera::getEntityFactories()
{
    return {
        {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("main", Engine::Entity::EntityType::CAMERA);
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::EntityInfo>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Viewport>(320, 240);
                auto viewport = entity->getComponent<Engine::CoreComponents::Viewport>();
                int width = 320, height = 240;
                if (config.find("width") != config.end())
                    viewport->width = std::any_cast<double>(config.at("width"));
                if (config.find("height") != config.end())
                    viewport->height = std::any_cast<double>(config.at("height"));
                if (viewport->width < width || viewport->height < height) {
                    viewport->width = width;
                    viewport->height = height;
                }
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Viewport>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Position>(0.0f, 0.0f, 0.0f);
                auto position = entity->getComponent<Engine::CoreComponents::Position>();
                if (config.find("pos_x") != config.end())
                    position->pos_x = std::any_cast<double>(config.at("pos_x"));
                if (config.find("pos_y") != config.end())
                    position->pos_y = std::any_cast<double>(config.at("pos_y"));
                if (config.find("pos_z") != config.end())
                    position->pos_z = std::any_cast<double>(config.at("pos_z"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Position>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Rotation>(0.0f, 0.0f, 0.0f);
                auto rotation = entity->getComponent<Engine::CoreComponents::Rotation>();
                if (config.find("axis_x") != config.end())
                    rotation->axis_x = std::any_cast<double>(config.at("axis_x"));
                if (config.find("axis_y") != config.end())
                    rotation->axis_y = std::any_cast<double>(config.at("axis_y"));
                if (config.find("axis_z") != config.end())
                    rotation->axis_z = std::any_cast<double>(config.at("axis_z"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Rotation>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Fov>(60);
                auto fov = entity->getComponent<Engine::CoreComponents::Fov>();
                if (config.find("fov") != config.end())
                    fov->value = std::any_cast<double>(config.at("fov"));
                if (fov->value < 60)
                    fov->value = 60;
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Fov>(entity->getID());

                return entity;
            }
        }
    };
}

std::vector<Engine::SystemFactoryInfo> Camera::getSystemFactories()
{
    return {};
}

void Camera::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Camera)
