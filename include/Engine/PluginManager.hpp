/*
** EPITECH PROJECT, 2025
** PluginManager.hpp
** File description:
** PluginManager
*/

#ifndef PLUGINMANAGER_HPP_
    #define PLUGINMANAGER_HPP_

    #include "Utils/DynamicLoader.hpp"
    #include "Engine/IPlugin.hpp"
    #include "Engine/Scene.hpp"

    #define PLUGINS_DIR "./plugins/"

namespace Engine
{
    class PluginManager
    {
    protected:
        PluginManager();
        ~PluginManager();

    private:
        static PluginManager *_instance;
        Utils::DynamicLoader _loader;

        struct PluginInfo 
        {
            std::shared_ptr<IPlugin> plugin;
            CreatePluginFunc func;
        };

        std::vector<PluginInfo> _plugins;
        std::unordered_map<Entity::EntityType, std::vector<std::shared_ptr<IPlugin>>> _pluginsByType;
        std::unordered_map<std::string, std::shared_ptr<IPlugin>> _pluginsByName;

        std::unordered_map<Entity::EntityType, 
            std::unordered_map<std::string, EntityCreationFunc>> _entityFactories;

        std::unordered_map<System::SystemType,
            std::unordered_map<std::string, SystemCreationFunc>> _systemFactories;

        void registerPluginFactories(std::shared_ptr<IPlugin> plugin, std::shared_ptr<Scene> scene);
        EntityCreationFunc createFactoryMethod(Entity::EntityType type,
            const std::string &entityName);

    public:
        static PluginManager &getInstance();
        void destroyInstance();

        PluginManager(const PluginManager &) = delete;
        PluginManager &operator=(const PluginManager &) = delete;

        const std::vector<PluginInfo> &getAllPlugins() const;
        std::vector<std::shared_ptr<IPlugin>> getPluginsByType(Entity::EntityType type) const;
        std::shared_ptr<IPlugin> getPluginByName(const std::string &name) const;

        std::shared_ptr<ECS::Entity> createEntity(Scene &scene, Entity::EntityType type,
            const std::string &entityName, const Entity::EntityConfig &params = {});
        std::shared_ptr<ECS::ISystem> createSystem(Scene &scene, System::SystemType type,
            const std::string &systemName, const System::SystemConfig &params = {});

        bool hasEntityFactory(Entity::EntityType type, const std::string &entityName) const;
        bool hasSystemFactory(System::SystemType type, const std::string &systemName) const;

        std::vector<std::string> getAvailableEntities(Entity::EntityType type) const;
        std::vector<std::string> getAvailableSystems(System::SystemType type) const;

        bool loadPlugin(const std::string &filepath, std::shared_ptr<Scene> scene);
        bool loadPluginsFromDirectory(const std::string &directory, std::shared_ptr<Scene> scene);
        bool unloadPlugin(const std::string &pluginName);
        void unloadAllPlugins();
    };
}

#endif /* !PLUGINMANAGER_HPP_ */
