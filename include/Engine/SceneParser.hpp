/*
** EPITECH PROJECT, 2025
** SceneParser.hpp
** File description:
** SceneParser
*/

#ifndef SCENEPARSER_HPP_
    #define SCENEPARSER_HPP_

    #include <libconfig.h++>
    #include <vector>
    #include "Engine/Types.hpp"

namespace Engine
{
    #define SCENE_EXTENSION ".scn"

    typedef std::unordered_map<std::string, std::vector<Entity::EntityConfig>> EntityList;
    typedef std::unordered_map<Entity::EntityType, EntityList> SceneEntityInfo;
    
    typedef std::unordered_map<std::string, std::vector<System::SystemConfig>> SystemList;
    typedef std::unordered_map<System::SystemType, SystemList> SceneSystemInfo;

    static constexpr Entity::EntityType MandatoryEntityTypes[] =
    {
        Entity::EntityType::CAMERA,
    };

    static constexpr System::SystemType MandatorySystemTypes[] =
    {
        // No time... (to die... sorry ><)
    };

    class SceneParser
    {
    private:
        std::string _filename;
        std::string _sceneName;
        SceneEntityInfo _entityInfos;
        SceneSystemInfo _systemInfos;

        bool checkFileExtension(const std::string &filename, const std::string &extension);
        void extractSceneName(const libconfig::Config &config);

        void parseEntityType(const libconfig::Config &config, Entity::EntityType type);
        void parseEntity(EntityList &entityList, const libconfig::Setting &pluginSetting);
        void parseEntityConfig(std::vector<Entity::EntityConfig> &entities, const libconfig::Setting &entitySetting);
        void validateMandatoryEntityTypes() const;

        void parseSystemType(const libconfig::Config &config, System::SystemType type);
        void parseSystem(SystemList &systemList, const libconfig::Setting &pluginSetting);
        void parseSystemConfig(std::vector<System::SystemConfig> &systems, const libconfig::Setting &systemSetting);
        void validateMandatorySystemTypes() const;

    public:
        const std::string getSceneName() const;
        const SceneEntityInfo getEntityInfos() const;
        const SceneSystemInfo getSystemInfos() const;

        void parseScene(const std::string &filename);
    };
}

#endif /* !SCENEPARSER_HPP_ */
