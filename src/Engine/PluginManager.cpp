/*
** EPITECH PROJECT, 2025
** PluginManager.cpp
** File description:
** PluginManager
*/

#include <filesystem>
#include <memory>
#include "Engine/PluginManager.hpp"
#include "Engine/EntityType.hpp"
#include "Engine/IPlugin.hpp"
#include "Utils/Logger.hpp"

namespace Engine
{
    PluginManager *PluginManager::_instance = nullptr;

    PluginManager::PluginManager() {}

    PluginManager::~PluginManager()
    {
        unloadAllPlugins();
    }

    PluginManager &PluginManager::getInstance()
    {
        if (!_instance)
            _instance = new PluginManager();
        return *_instance;
    }

    void PluginManager::destroyInstance()
    {
        if (!_instance)
            return;
        unloadAllPlugins();
        delete(_instance);
    }

    bool PluginManager::loadPlugin(const std::string &filepath, std::shared_ptr<Scene> scene)
    {
        PluginInfo info = {};
        auto &logger = Utils::Logger::getInstance();

        logger.info("Loading plugin from %s", filepath.c_str());
        try {
            _loader.openFile(filepath);
            _loader.addSym(DLSYBMOL);
            info.func = _loader.loadFunc<CreatePluginFunc>(DLSYBMOL);
            IPlugin *rawPlugin = info.func();
            if (!rawPlugin) {
                logger.error("Plugin creation function returned null");
                return false;
            }
            info.plugin = std::shared_ptr<IPlugin>(rawPlugin);
            if (!info.plugin->initialize(scene)) {
                logger.error("Plugin '%s' failed to initialize", info.plugin->getName().c_str());
                return false;
            }
            registerPluginFactories(info.plugin, scene);
            _plugins.push_back(info);
            _pluginsByType[info.plugin->getEntityType()].push_back(info.plugin);
            _pluginsByName[info.plugin->getName()] = info.plugin;
        } catch (std::exception &e) {
            logger.error("Failed to load plugin: %s", e.what());
            return false;
        }
        return true;
    }

    bool PluginManager::loadPluginsFromDirectory(const std::string &directory, std::shared_ptr<Scene> scene)
    {
        auto &logger = Utils::Logger::getInstance();

        if (!std::filesystem::exists(directory)) {
            logger.warning("Plugin directory does not exist: %s", directory.c_str());
            return false;
        }
        try {
            bool pluginsFound = false;

            for (const auto &entry : std::filesystem::directory_iterator(directory)) {
                if (entry.is_regular_file() && entry.path().extension() == PLUGIN_EXTENSION) {
                    pluginsFound = true;
                    std::string path = entry.path().string();
                    if (!loadPlugin(path, scene))
                        logger.warning("Failed to load plugin from %s", path.c_str());
                }
            }
            if (!pluginsFound) {
                logger.info("No plugins found in directory: %s", directory.c_str());
                return false;
            }
        } catch (std::exception &e) {
            logger.error("Error loading plugins from directory %s: %s", directory.c_str(), e.what());
            return false;
        }
        return true;
    }

    bool PluginManager::unloadPlugin(const std::string &pluginName)
    {
        for (auto it = _plugins.begin(); it != _plugins.end(); ++it) {
            if (it->plugin->getName() == pluginName) {
                it->plugin->shutdown();
                auto &typePlugins = _pluginsByType[it->plugin->getEntityType()];
                for (auto it2 = typePlugins.begin(); it2 != typePlugins.end(); ++it2) {
                    if ((*it2)->getName() == pluginName) {
                        typePlugins.erase(it2);
                        break;
                    }
                }
                _pluginsByName.erase(pluginName);
                _plugins.erase(it);
                return true;
            }
        }
        return false;
    }

    void PluginManager::unloadAllPlugins()
    {
        for (auto &info : _plugins)
            info.plugin->shutdown();
        _plugins.clear();
        _pluginsByType.clear();
        _pluginsByName.clear();
        _entityFactories.clear();
        _systemFactories.clear();
    }

    const std::vector<PluginManager::PluginInfo> &PluginManager::getAllPlugins() const
    {
        return _plugins;
    }

    std::vector<std::shared_ptr<IPlugin>> PluginManager::getPluginsByType(Entity::EntityType type) const
    {
        if (_pluginsByType.find(type) == _pluginsByType.end())
            return {};
        return _pluginsByType.at(type);
    }

    std::shared_ptr<IPlugin> PluginManager::getPluginByName(const std::string &name) const
    {
        if (_pluginsByName.find(name) == _pluginsByName.end())
            return nullptr;
        return _pluginsByName.at(name);
    }

    void PluginManager::registerPluginFactories(std::shared_ptr<IPlugin> plugin, std::shared_ptr<Scene> scene)
    {
        auto &logger = Utils::Logger::getInstance();
        logger.debug("Registering factories for plugin '%s'", plugin->getName().c_str());
        const auto &entityFactories = plugin->getEntityFactories();
        for (const auto &factoryInfo : entityFactories) {
            Entity::EntityType type = factoryInfo.entityType;
            std::string entityName = factoryInfo.entityName;
            EntityCreationFunc factory = factoryInfo.createFunction;
            if (_entityFactories[type].find(entityName) != _entityFactories[type].end()) {
                logger.warning("Entity factory for '%s' of type '%s' already registered, skipping",
                    entityName.c_str(), Entity::getEntityTypeName(type));
                continue;
            }
            _entityFactories[type][entityName] = factory;
            logger.debug("Registered entity factory for '%s' of type '%s'",
                entityName.c_str(), Entity::getEntityTypeName(type));
        }
        const auto &systemFactories = plugin->getSystemFactories();
        for (const auto &factoryInfo : systemFactories) {
            System::SystemType type = factoryInfo.systemType;
            std::string systemName = factoryInfo.systemName;
            SystemCreationFunc factory = factoryInfo.createFunction;
            if (_systemFactories[type].find(systemName) != _systemFactories[type].end()) {
                logger.warning("System factory for '%s' of type '%s' already registered, skipping",
                    systemName.c_str(), System::getSystemTypeName(type).c_str());
                continue;
            }
            _systemFactories[type][systemName] = factory;
            logger.debug("Registered system factory for '%s' of type '%s'",
                systemName.c_str(), System::getSystemTypeName(type).c_str());
        }
        plugin->configureSystems(scene);
    }

    EntityCreationFunc PluginManager::createFactoryMethod(Entity::EntityType type,
        const std::string &entityName)
    {
        auto &logger = Utils::Logger::getInstance();

        auto typeIt = _entityFactories.find(type);
        if (typeIt == _entityFactories.end()) {
            logger.error("No factory for entity type '%s'", Entity::getEntityTypeName(type));
            return nullptr;
        }
        auto factoryIt = typeIt->second.find(entityName);
        if (factoryIt == typeIt->second.end()) {
            logger.error("No factory for entity '%s' of type '%s'",
                entityName.c_str(), Entity::getEntityTypeName(type));
            return nullptr; 
        }
        logger.debug("PluginManager: Create factory method for entity '%s' of type '%s'", 
            entityName.c_str(), Entity::getEntityTypeName(type));
        return factoryIt->second;
    }

    std::shared_ptr<ECS::Entity> PluginManager::createEntity(Scene &scene, Entity::EntityType type,
        const std::string &entityName, const Entity::EntityConfig &params)
    {
        auto &logger = Utils::Logger::getInstance();
        std::shared_ptr<ECS::Entity> entity = nullptr;
        EntityCreationFunc createFunc = createFactoryMethod(type, entityName);


        if (!createFunc) {
            logger.error("PluginManager: Entity Creation Func of '%s' for '%s' is null",
                Entity::getEntityTypeName(type), entityName.c_str());
            return nullptr;
        }
        try {
            logger.debug("PluginManager: Creating entity '%s' of type '%s'", 
                entityName.c_str(), Entity::getEntityTypeName(type));
            entity = createFunc(scene, params);
            if (!entity) {
                logger.error("PluginManager: Entity Creation of '%s' for '%s' failed",
                    Entity::getEntityTypeName(type), entityName.c_str());
                return nullptr;
            }
        } catch (const std::exception& e) {
            logger.error("Exception while creating entity '%s' of type '%s': %s",
                entityName.c_str(), Entity::getEntityTypeName(type), e.what());
            return nullptr;
        }
        logger.debug("PluginManager: entity '%s' of type '%s' created!", 
            entityName.c_str(), Entity::getEntityTypeName(type));
        return entity;
    }

    std::shared_ptr<ECS::ISystem> PluginManager::createSystem(Scene &scene, System::SystemType type,
        const std::string &systemName, const System::SystemConfig &params)
    {
        auto &logger = Utils::Logger::getInstance();

        auto typeIt = _systemFactories.find(type);
        if (typeIt == _systemFactories.end()) {
            logger.error("No factory for system type '%s'", System::getSystemTypeName(type).c_str());
            return nullptr;
        }
        auto factoryIt = typeIt->second.find(systemName);
        if (factoryIt == typeIt->second.end()) {
            logger.error("No factory for system '%s' of type '%s'",
                systemName.c_str(), System::getSystemTypeName(type).c_str());
            return nullptr; 
        }
        logger.debug("Creating system '%s' of type '%s'", 
            systemName.c_str(), System::getSystemTypeName(type).c_str());
        SystemCreationFunc createFunc = factoryIt->second;
        if (!createFunc)
            logger.error("PluginManager: Entity Creation Func of '%s' for '%s' returns null",
                System::getSystemTypeName(type).c_str(), systemName.c_str());
        return createFunc(scene, params);
    }

    bool PluginManager::hasEntityFactory(Entity::EntityType type, const std::string &entityName) const
    {
        auto typeIt = _entityFactories.find(type);
        if (typeIt == _entityFactories.end())
            return false;
        return typeIt->second.find(entityName) != typeIt->second.end();
    }

    bool PluginManager::hasSystemFactory(System::SystemType type, const std::string &systemName) const
    {
        auto typeIt = _systemFactories.find(type);
        if (typeIt == _systemFactories.end())
            return false;
        return typeIt->second.find(systemName) != typeIt->second.end();
    }

    std::vector<std::string> PluginManager::getAvailableEntities(Entity::EntityType type) const
    {
        std::vector<std::string> result;
        auto typeIt = _entityFactories.find(type);

        if (typeIt == _entityFactories.end())
            return result;
        for (const auto &[entityName, _] : typeIt->second)
            result.push_back(entityName);
        return result;
    }

    std::vector<std::string> PluginManager::getAvailableSystems(System::SystemType type) const
    {
        std::vector<std::string> result;
        auto typeIt = _systemFactories.find(type);
        
        if (typeIt == _systemFactories.end())
            return result;
        for (const auto &[systemName, _] : typeIt->second)
            result.push_back(systemName);
        return result;
    }
}
