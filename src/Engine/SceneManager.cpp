/*
** EPITECH PROJECT, 2025
** SceneManager.cpp
** File description:
** SceneManager
*/

#include "Utils/Logger.hpp"
#include "Engine/SceneManager.hpp"
#include "Engine/PluginManager.hpp"

namespace Engine
{
    SceneManager::~SceneManager()
    {
        _scenes.clear();
        _currentScene.reset();
    }

    void SceneManager::loadScene(const std::string &filename)
    {
        auto &pluginManager = PluginManager::getInstance();
        auto &logger = Utils::Logger::getInstance();

        logger.debug("SceneManager: load scene from '%s'", filename.c_str());
        try {
            _sceneParser.parseScene(filename);
            std::string sceneName = _sceneParser.getSceneName();
            std::shared_ptr<Scene> scene = std::make_shared<Scene>(sceneName);
            logger.debug("SceneManager: load Plugins from directory");
            if (!pluginManager.loadPluginsFromDirectory(PLUGINS_DIR, scene))
                return;
            logger.debug("SceneManager: assign Scene '%s' parsed data", sceneName.c_str());
            SceneEntityInfo sceneInfos = _sceneParser.getEntityInfos();
            for (const auto &sceneInfo : sceneInfos)
                for (const auto &entityList : sceneInfo.second)
                    for (const auto &entityConfig : entityList.second) {
                        scene->createEntity(sceneInfo.first, entityList.first, entityConfig);
                        logger.debug("Entity created!");
                }
            _scenes[sceneName] = scene;
            _currentScene = scene;
            logger.debug("SceneManager: Scene '%s' loaded successfully", sceneName.c_str());
            // Implement the same for Systems here if time...  (no time...) 
        } catch (const std::exception &e) {
            logger.error(e.what());
        }
    }

    void SceneManager::unloadScene(const std::string &sceneName)
    {
        auto &logger = Utils::Logger::getInstance();

        if (_scenes.find(sceneName) == _scenes.end()) {
            logger.error("SceneManager: Unloading unregistered scene");
            return;
        }
        if (_currentScene && _currentScene->getName() == sceneName)
            _currentScene.reset();
        logger.debug("SceneManager: %s unloaded.", sceneName.c_str());
        _scenes.erase(sceneName);
    }

    void SceneManager::saveScene(const std::string &filename)
    {
        (void)filename;
    }

    std::shared_ptr<Scene> SceneManager::getCurrentScene() const
    {
        return _currentScene;
    }

    std::unordered_map<std::string, std::shared_ptr<Scene>> SceneManager::getAllScenes() const
    {
        return _scenes;
    }
}
