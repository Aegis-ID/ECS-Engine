/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** Viewport
*/

#ifndef VIEWPORT_HPP_
    #define VIEWPORT_HPP_

namespace Engine::CoreComponents
{
    struct Viewport
    {
        int width;
        int height;

        Viewport(){}
        Viewport(int width, int height)
            :   width(width), height(height) {}
    };
}

#endif /* !VIEWPORT_HPP_ */
