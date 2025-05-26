/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** RTConverter
*/

#include "Engine/RTConverter.hpp"
#include "ECS/Entity.hpp"
#include "Engine/SceneManager.hpp"
#include "Utils/Logger.hpp"

namespace Engine
{
    RTConverter::RTConverter(){}

    RTConverter::~RTConverter(){}

    void RTConverter::loadConverter(SceneManager &sceneManager)
    {
        _sceneManager = sceneManager;
    }

    void RTConverter::convertScenes()
    {
        auto &logger = Utils::Logger::getInstance();
        auto scenes = _sceneManager.getAllScenes();

        try {
            for (const auto &scene : scenes)
                for (const auto &entity : scene.second->getEntityManager()->getAllEntities())
                    convertEntity(entity.second);
        } catch (std::exception &e) {
            logger.error("RTConverter: '%s'", e.what());
        }
    }

    void RTConverter::convertEntity(const std::shared_ptr<ECS::Entity> entity)
    {
        (void)entity;
        // create one function per handled entity (these are specific cases and logic, so no worry if
        // it seems repetitive.)
    }
}
