/*
** EPITECH PROJECT, 2025
** Color.hpp
** File description:
** Color
*/

#ifndef COLOR_HPP_
    #define COLOR_HPP_

namespace Engine::CoreComponents
{
    struct Color
    {
        short r;
        short g;
        short b;

        Color(){}
        Color(short r, short g, short b)
            :   r(r), g(g), b(b) {}
    };
}

#endif /* !COLOR_HPP_ */
