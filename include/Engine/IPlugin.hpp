/*
** EPITECH PROJECT, 2025
** IPlugin.hpp
** File description:
** IPlugin
** Love this side of video games, hope Bethesda with TES VI will do this right...
*/

#ifndef IPLUGIN_HPP_
    #define IPLUGIN_HPP_

    #include <string>
    #include <memory>
    #include <vector>
    #include "ECS/Entity.hpp"
    #include "ECS/ISystem.hpp"
    #include "Engine/Types.hpp"

namespace Engine
{
    #define DLSYBMOL "createPlugin"
    #define PLUGIN_EXTENSION ".so"

    typedef std::tuple<int, int, int> Version;
    
    class Scene;

    using EntityCreationFunc = std::shared_ptr<ECS::Entity> (*)(Scene &, const Entity::EntityConfig &);
    using SystemCreationFunc = std::shared_ptr<ECS::ISystem> (*)(Scene &, const System::SystemConfig &);

    struct EntityFactoryInfo
    {
        std::string entityName;
        Entity::EntityType entityType;
        EntityCreationFunc createFunction;
    };

    struct SystemFactoryInfo
    {
        std::string systemName;
        System::SystemType systemType;
        SystemCreationFunc createFunction;
    };

    class IPlugin
    {
    public:
        virtual ~IPlugin() = default;

        virtual std::string getName() const = 0;
        virtual std::string getAuthor() const = 0;
        virtual std::string getDescription() const = 0;
        virtual Version getVersion() const = 0;

        virtual Entity::EntityType getEntityType() const = 0;
        virtual System::SystemType getSystemType() const = 0;
        virtual ECS::Signature getEntitySignature() const = 0;

        virtual bool initialize(std::shared_ptr<Scene> scene) = 0;
        virtual bool shutdown() = 0;

        virtual std::vector<EntityFactoryInfo> getEntityFactories() = 0;
        virtual std::vector<SystemFactoryInfo> getSystemFactories() = 0;

        virtual void configureSystems(std::shared_ptr<Scene> scene) = 0;
    };

    typedef IPlugin *(*CreatePluginFunc)();

    #define EXPORT_PLUGIN(PluginClass) \
        extern "C" Engine::IPlugin *createPlugin() \
        { \
            return new PluginClass(); \
        }
}

#endif /* !IPLUGIN_HPP_ */
