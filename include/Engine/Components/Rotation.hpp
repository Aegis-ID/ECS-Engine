/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** Rotation
*/

#ifndef ROTATION_HPP_
    #define ROTATION_HPP_

namespace Engine::CoreComponents
{
    struct Rotation
    {
        double axis_x;
        double axis_y;
        double axis_z;

        Rotation(){}
        Rotation(double x, double y, double z)
            :   axis_x(x), axis_y(y), axis_z(z){}

    };
}

#endif /* !ROTATION_HPP_ */
