/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** Fov
*/

#ifndef FOV_HPP_
    #define FOV_HPP_

namespace Engine::CoreComponents
{
    struct Fov
    {
        float value;

        Fov(){}
        Fov(float value)
            :   value(value) {}
    };
}

#endif /* !FOV_HPP_ */
