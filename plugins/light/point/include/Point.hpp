/*
** EPITECH PROJECT, 2025
** Point.hpp
** File description:
** Point
** One of the only thing bethesda did right
*/

#ifndef POINTPLUGIN_HPP_
    #define POINTPLUGIN_HPP_

    #include "Engine/Scene.hpp"
    #include "Engine/IPlugin.hpp"
    #include "Engine/CoreComponents.hpp"
    #include "Engine/CoreSystems.hpp"

class Point : public Engine::IPlugin
{
    private:
        ECS::Signature _signature;

    public:
        Point() = default;
        ~Point() = default;

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

#endif /* !POINTPLUGIN_HPP_ */
