/*
** EPITECH PROJECT, 2025
** Sphere.hpp
** File description:
** Sphere
*/

#ifndef SPHEREPLUGIN_HPP_
    #define SPHEREPLUGIN_HPP_

    #include "Engine/Scene.hpp"
    #include "Engine/IPlugin.hpp"
    #include "Engine/CoreComponents.hpp"
    #include "Engine/CoreSystems.hpp"

class Sphere : public Engine::IPlugin
{
    private:
        ECS::Signature _signature;

        static void configureEntityInfo(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene);
        static void configurePosition(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);
        static void configureRotation(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);
        static void configureScale(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);
        static void configureColor(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);
        static void configureMaterial(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);
        static void configureRadius(std::shared_ptr<ECS::Entity> entity, Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);

        static std::shared_ptr<ECS::Entity> createSphereEntity(Engine::Scene &scene, 
            const Engine::Entity::EntityConfig& config);

    public:
        Sphere() = default;
        ~Sphere() = default;

        std::string getName() const override;
        std::string getAuthor() const override;
        std::string getDescription() const override;
        Engine::Version getVersion() const override;

        Engine::Entity::EntityType getEntityType() const override;
        Engine::System::SystemType getSystemType() const override;
        ECS::Signature getEntitySignature() const override;

        bool initialize(std::shared_ptr<Engine::Scene> scene) override;
        bool shutdown() override;

        std::vector<Engine::EntityFactoryInfo> getEntityFactories() override;
        std::vector<Engine::SystemFactoryInfo> getSystemFactories() override;

        void configureSystems(std::shared_ptr<Engine::Scene> scene) override;
};

#endif /* !SPHEREPLUGIN_HPP_ */
