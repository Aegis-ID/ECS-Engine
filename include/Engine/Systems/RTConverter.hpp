/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** RTConverter
*/

#ifndef RTCONVERTER_HPP_
    #define RTCONVERTER_HPP_

#include "ECS/EntityManager.hpp"
#include "Engine/SceneManager.hpp"

namespace Engine
{
    class RTConverter
    {
    private:
        // Put ray class here
        SceneManager _sceneManager;


        void convertCamera(const std::shared_ptr<ECS::Entity> entity);
        void convertAmbient(const std::shared_ptr<ECS::Entity> entity);

        void convertEntity(const std::shared_ptr<ECS::Entity> entity);
    public:
        RTConverter();
        ~RTConverter();

        void loadConverter(SceneManager &sceneManager);
        void convertScenes();
    };
}

#endif /* !RTCONVERTER_HPP_ */
