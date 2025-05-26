/*
** EPITECH PROJECT, 2025
** Position.hpp
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

namespace Engine::CoreComponents
{
    struct Position
    {
        double pos_x;
        double pos_y;
        double pos_z;

        Position(){}
        Position(double x, double y, double z)
            :   pos_x(x), pos_y(y), pos_z(z) {}
    };
}

#endif /* !POSITION_HPP_ */
