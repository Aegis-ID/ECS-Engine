/*
** EPITECH PROJECT, 2025
** Ambient.hpp
** File description:
** Ambient
** One of the only thing bethesda did right
*/

#ifndef AMBIENTPLUGIN_HPP_
    #define AMBIENTPLUGIN_HPP_

    #include "Engine/Scene.hpp"
    #include "Engine/IPlugin.hpp"
    #include "Engine/CoreComponents.hpp"
    #include "Engine/CoreSystems.hpp"

class Ambient : public Engine::IPlugin
{
    private:
        ECS::Signature _signature;

    public:
        Ambient() = default;
        ~Ambient() = default;

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

#endif /* !AMBIENTPLUGIN_HPP_ */
