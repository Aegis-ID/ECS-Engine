/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** IRenderer
*/

#ifndef IRENDERER_HPP_
    #define IRENDERER_HPP_

    #include "ECS/Entity.hpp"
    #include "ECS/ISystem.hpp"

namespace Engine
{
    struct RendererSettings
    {
        int window_height
        int window_width;
    };

    class IRenderer : public ECS::ISystem
    {
    public:
        virtual ~IRenderer() = default;

        virtual void initWindow() = 0;
        virtual void closeWindow() = 0;
        virtual bool isWindowOpen() = 0;

        virtual void clearScreen() = 0;
        virtual void drawScreen(ECS::Entity) = 0;
        virtual void refreshScreen() = 0;
    }
}

#endif /* !IRENDERER_HPP_ */
