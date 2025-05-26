/*
** EPITECH PROJECT, 2025
** Plane.cpp
** File description:
** Plane
** One of the only thing bethesda did right
*/

#include "include/Plane.hpp"

std::string Plane::getName() const
{
    return "plane";
}

std::string Plane::getAuthor() const
{
    return "Paul";
}

std::string Plane::getDescription() const
{
    return "Plane Plugin";
}

Engine::Version Plane::getVersion() const
{
    return {1, 0, 0};
}

Engine::Entity::EntityType Plane::getEntityType() const
{
    return Engine::Entity::EntityType::PRIMITIVE;
}

Engine::System::SystemType Plane::getSystemType() const
{
    return Engine::System::SystemType::UNKNOWN;
}

bool Plane::initialize(std::shared_ptr<Engine::Scene> scene)
{
    auto componentManager = scene->getComponentManager();

    componentManager->registerComponent<Engine::CoreComponents::EntityInfo>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::EntityInfo>());

    componentManager->registerComponent<Engine::CoreComponents::Scale>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Scale>());

    componentManager->registerComponent<Engine::CoreComponents::Rotation>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Rotation>());

    componentManager->registerComponent<Engine::CoreComponents::Position>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Position>());

    componentManager->registerComponent<Engine::CoreComponents::Color>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Color>());

    componentManager->registerComponent<Engine::CoreComponents::Material>();
    _signature.set(componentManager->getComponentType<Engine::CoreComponents::Material>());

    return true;
}

bool Plane::shutdown()
{
    return true;
}

ECS::Signature Plane::getEntitySignature() const
{
    return _signature;
}

std::vector<Engine::EntityFactoryInfo> Plane::getEntityFactories()
{
    return {
        {
            getName(),
            getEntityType(),
            [](Engine::Scene &scene, const Engine::Entity::EntityConfig &config)
            {
                auto entity = scene.getEntityManager()->createEntity();

                entity->addComponent<Engine::CoreComponents::EntityInfo>("plane", Engine::Entity::EntityType::PRIMITIVE);
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

                entity->addComponent<Engine::CoreComponents::Rotation>(0.0f, 0.0f, 0.0f);
                auto rotation = entity->getComponent<Engine::CoreComponents::Rotation>();
                if (config.find("axis_x") != config.end())
                    rotation->axis_x = std::any_cast<double>(config.at("axis_x"));
                if (config.find("axis_y") != config.end())
                    rotation->axis_y = std::any_cast<double>(config.at("axis_y"));
                if (config.find("axis_z") != config.end())
                    rotation->axis_z = std::any_cast<double>(config.at("axis_z"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Rotation>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Scale>(0.0f);
                auto scale = entity->getComponent<Engine::CoreComponents::Scale>();
                if (config.find("scale") != config.end())
                    scale->scale = std::any_cast<double>(config.at("scale"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Scale>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Color>(0, 0, 0);
                auto color = entity->getComponent<Engine::CoreComponents::Color>();
                if (config.find("r") != config.end())
                    color->r = std::any_cast<short>(config.at("r"));
                if (config.find("g") != config.end())
                    color->g = std::any_cast<short>(config.at("g"));
                if (config.find("b") != config.end())
                    color->b = std::any_cast<short>(config.at("b"));
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Color>(entity->getID());

                entity->addComponent<Engine::CoreComponents::Material>();
                auto material = entity->getComponent<Engine::CoreComponents::Material>();
                double diff_x = 0, diff_y = 0, diff_z = 0;
                if (config.find("diff_x") != config.end())
                    diff_x = std::any_cast<double>(config.at("diff_x"));
                if (config.find("diff_y") != config.end())
                    diff_y = std::any_cast<double>(config.at("diff_y"));
                if (config.find("diff_z") != config.end())
                    diff_z = std::any_cast<double>(config.at("diff_z"));
                material->diffuse = (Math::Vec3){diff_x, diff_y, diff_z};
                double spec_x = 0, spec_y = 0, spec_z = 0;
                if (config.find("spec_x") != config.end())
                    spec_x = std::any_cast<double>(config.at("spec_x"));
                if (config.find("spec_y") != config.end())
                    spec_y = std::any_cast<double>(config.at("spec_y"));
                if (config.find("spec_z") != config.end())
                    spec_z = std::any_cast<double>(config.at("spec_z"));
                material->specular = (Math::Vec3){spec_x, spec_y, spec_z};
                float shininess = 0, reflect = 42, ior = 42, transmit = 0;
                if (config.find("shininess") != config.end())
                    shininess = std::any_cast<float>(config.at("shininess"));
                material->shininess = shininess;
                if (config.find("reflect") != config.end()) {
                    reflect = std::any_cast<float>(config.at("reflect"));
                    material->reflect = reflect;
                } else if (config.find("refrac") != config.end())
                    ior = std::any_cast<float>(config.at("refrac"));
                material->ior = ior;
                if (config.find("transmit") != config.end())
                    transmit = std::any_cast<float>(config.at("transmit"));
                material->transmit = transmit;
                scene.getEntityManager()->onComponentAdded<Engine::CoreComponents::Material>(entity->getID());

                return entity;
            }
        }
    };
}

std::vector<Engine::SystemFactoryInfo> Plane::getSystemFactories()
{
    return {};
}

void Plane::configureSystems(std::shared_ptr<Engine::Scene> scene)
{
    (void)scene;
}

EXPORT_PLUGIN(Plane)