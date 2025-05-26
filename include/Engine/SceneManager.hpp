/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** SceneManager
*/

#ifndef SCENEMANAGER_HPP_
    #define SCENEMANAGER_HPP_

    #include <unordered_map>
    #include <memory>

    #include "Engine/Scene.hpp"
    #include "Engine/SceneParser.hpp"

namespace Engine
{
    class SceneManager
    {
    private:
        SceneParser _sceneParser;

        std::shared_ptr<Scene> _currentScene;
        std::unordered_map<std::string, std::shared_ptr<Scene>> _scenes;

    public:
        ~SceneManager();

        void loadScene(const std::string &filename);
        void unloadScene(const std::string &sceneName);
        void saveScene(const std::string &filename);

        std::shared_ptr<Scene> getCurrentScene() const;
        std::unordered_map<std::string, std::shared_ptr<Scene>> getAllScenes() const;
    };
}

#endif /* !SCENEMANAGER_HPP_ */
