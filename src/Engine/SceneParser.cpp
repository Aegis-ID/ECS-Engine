/*
** EPITECH PROJECT, 2025
** SceneParser.hpp
** File description:
** SceneParser
*/

#include <stdexcept>
#include "Engine/SceneParser.hpp"

namespace Engine
{
    const std::string SceneParser::getSceneName() const
    {
        return _sceneName;
    }

    const SceneEntityInfo SceneParser::getEntityInfos() const
    {
        return _entityInfos;
    }

    const SceneSystemInfo SceneParser::getSystemInfos() const
    {
        return _systemInfos;
    }

    bool SceneParser::checkFileExtension(const std::string &filename, const std::string &extension)
    {
        size_t dotPos = filename.find_last_of(".");

        if (dotPos == std::string::npos)
            return false;
        return filename.substr(dotPos) == extension;
    }

    void SceneParser::extractSceneName(const libconfig::Config &config)
    {
        try {
            _sceneName = config.lookup("scene").c_str();
        } catch (const libconfig::SettingNotFoundException &e) {
            throw std::runtime_error("SceneParser: Scene name not found in configuration file");
        }
    }

    void SceneParser::parseEntityType(const libconfig::Config &config, Entity::EntityType type)
    {
        std::string typeName = Entity::getEntityTypeName(type);
        if (!config.exists(typeName))
            return;

        const libconfig::Setting &entityTypeSettings = config.lookup(typeName);
        EntityList entityList;

        for (int i = 0; i < entityTypeSettings.getLength(); ++i) {
            const libconfig::Setting &entitySetting = entityTypeSettings[i];
            parseEntity(entityList, entitySetting);
        }
        if (!entityList.empty())
            _entityInfos[type] = entityList;
    }

    void SceneParser::parseEntity(EntityList &entityList, const libconfig::Setting &entitySetting)
    {
        std::string entityName = entitySetting.getName();

        if (entitySetting.isList()) {
            std::vector<Entity::EntityConfig> entities;
            for (int i = 0; i < entitySetting.getLength(); ++i) {
                const libconfig::Setting &it = entitySetting[i];
                parseEntityConfig(entities, it);
            }
            if (!entities.empty())
                entityList[entityName] = entities;
        }
    }

    void SceneParser::parseEntityConfig(std::vector<Entity::EntityConfig> &entities,
        const libconfig::Setting &entitySetting)
    {
        Entity::EntityConfig entityConfig;

        for (int i = 0; i < entitySetting.getLength(); ++i) {
            const libconfig::Setting &member = entitySetting[i];
            std::string memberName = member.getName();
            switch (member.getType()) {
                case libconfig::Setting::Type::TypeInt:
                    entityConfig[memberName] = static_cast<int>(member);
                    break;
                case libconfig::Setting::Type::TypeInt64:
                    entityConfig[memberName] = static_cast<long int>(member);
                    break;
                case libconfig::Setting::Type::TypeFloat:
                    entityConfig[memberName] = static_cast<double>(member);
                    break;
                case libconfig::Setting::Type::TypeString:
                    entityConfig[memberName] = std::string(member.c_str());
                    break;
                case libconfig::Setting::Type::TypeBoolean:
                    entityConfig[memberName] = static_cast<bool>(member);
                    break;
                default:
                    throw std::runtime_error("SceneParser: Unsupported value type for " + memberName);
            }
        }
        entities.push_back(entityConfig);
    }

    void SceneParser::validateMandatoryEntityTypes() const
    {
        for (const auto &mandatoryType : MandatoryEntityTypes)
            if (_entityInfos.find(mandatoryType) == _entityInfos.end())
                throw std::runtime_error("SceneParser: Mandatory entity type '" +
                    Entity::getEntityTypeName(mandatoryType) + "' is missing from the scene.");
    }

    void SceneParser::parseSystemType(const libconfig::Config &config, System::SystemType type)
    {
        std::string typeName = System::getSystemTypeName(type);
        if (!config.exists(typeName))
            return;

        const libconfig::Setting &systemTypeSettings = config.lookup(typeName);
        SystemList systemList;

        for (int i = 0; i < systemTypeSettings.getLength(); ++i) {
            const libconfig::Setting &systemSetting = systemTypeSettings[i];
            parseSystem(systemList, systemSetting);
        }
        if (!systemList.empty())
            _systemInfos[type] = systemList;
    }

    void SceneParser::parseSystem(SystemList &systemList, const libconfig::Setting &systemSetting)
    {
        std::string systemName = systemSetting.getName();

        if (systemSetting.isList()) {
            std::vector<System::SystemConfig> systems;
            for (int i = 0; i < systemSetting.getLength(); ++i) {
                const libconfig::Setting &it = systemSetting[i];
                parseSystemConfig(systems, it);
            }
            if (!systems.empty())
                systemList[systemName] = systems;
        }
    }

    void SceneParser::parseSystemConfig(std::vector<System::SystemConfig> &systems,
        const libconfig::Setting &systemSetting)
    {
        System::SystemConfig systemConfig;

        for (int i = 0; i < systemSetting.getLength(); ++i) {
            const libconfig::Setting &member = systemSetting[i];
            std::string memberName = member.getName();
            switch (member.getType()) {
                case libconfig::Setting::Type::TypeInt:
                    systemConfig[memberName] = static_cast<int>(member);
                    break;
                case libconfig::Setting::Type::TypeInt64:
                    systemConfig[memberName] = static_cast<long int>(member);
                    break;
                case libconfig::Setting::Type::TypeFloat:
                    systemConfig[memberName] = static_cast<double>(member);
                    break;
                case libconfig::Setting::Type::TypeString:
                    systemConfig[memberName] = std::string(member.c_str());
                    break;
                case libconfig::Setting::Type::TypeBoolean:
                    systemConfig[memberName] = static_cast<bool>(member);
                    break;
                default:
                    throw std::runtime_error("SceneParser: Unsupported value type for " + memberName);
            }
        }
        systems.push_back(systemConfig);
    }

    void SceneParser::validateMandatorySystemTypes() const
    {
        for (const auto &mandatoryType : MandatorySystemTypes)
            if (_systemInfos.find(mandatoryType) == _systemInfos.end())
                throw std::runtime_error("SceneParser: Mandatory system type '" +
                    System::getSystemTypeName(mandatoryType) + "' is missing from the scene.");
    }

    void SceneParser::parseScene(const std::string &filename)
    {
        if (!checkFileExtension(filename, SCENE_EXTENSION))
            throw std::runtime_error("SceneParser: Invalid scene file extension. Expected "
                + std::string(SCENE_EXTENSION));
        _sceneName.clear();
        _entityInfos.clear();
        _systemInfos.clear();
        libconfig::Config config;
        try {
            config.readFile(filename.c_str());
            extractSceneName(config);
            for (int typeIndex = Entity::EntityType::CAMERA; typeIndex < Entity::EntityType::UNKNOWN; ++typeIndex)
                parseEntityType(config, static_cast<Entity::EntityType>(typeIndex));
            validateMandatoryEntityTypes();
            for (int typeIndex = System::SystemType::RENDERING; typeIndex < System::SystemType::UNKNOWN; ++typeIndex)
                parseSystemType(config, static_cast<System::SystemType>(typeIndex));
            validateMandatorySystemTypes();
        } catch (const libconfig::FileIOException &e) {
            throw std::runtime_error("SceneParser: Error reading scene file: " + filename);
        } catch (const libconfig::ParseException &e) {
            throw std::runtime_error("SceneParser: Parse error in scene file " + filename
                + " at line "+ std::to_string(e.getLine()) + ": " + e.getError());
        }
    }
}
