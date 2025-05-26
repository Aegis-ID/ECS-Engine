/*
** EPITECH PROJECT, 2025
** Material.hpp
** File description:
** Material
*/

#ifndef MATERIAL_HPP_
    #define MATERIAL_HPP_

#include "Utils/Math.hpp"

namespace Engine::CoreComponents
{
    struct Material
    {
        Math::Vec3  diffuse;
        Math::Vec3  specular;
        float shininess;        //phong
        float reflect;          // 0=mat, 1=miroir
        float transmit;         // 0=opaque, 1=transparent
        float ior;              // indice de réfraction
        
        Material(){}
        Material(Math::Vec3 diff, Math::Vec3 spec, float shine, float reflect, float transmit, float ior)
            :   diffuse(diff), specular(spec), shininess(shine), reflect(reflect), transmit(transmit), ior(ior) {}
    };
}

#endif /* !MATERIAL_HPP_ */
