/*
** EPITECH PROJECT, 2025
** Scale.hpp
** File description:
** Scale
*/

#ifndef SCALE_HPP_
    #define SCALE_HPP_

namespace Engine::CoreComponents
{
    struct Scale
    {
        double scale;

        Scale(){}
        Scale(double scale) : scale(scale) {}
    };
}

#endif /* !SCALE_HPP_ */
