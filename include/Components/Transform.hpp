/*
** EPITECH PROJECT, 2025
** Transform.hpp
** File description:
** Transform
*/

#ifndef __TRANSFORM_H__
    #define __TRANSFORM_H__

#include "../ComponentWrapper.hpp"
#include "../Vector.hpp"

namespace ECS::Components
{
    class TransformComponent : public IComponentWrapper
    {
    private:
        Vec3<float> _position;
        Vec3<float> _velocity;
        Vec3<float> _scale;
    public:
        void setPosition(const Vec3<float> &pos) { _position = pos; }
        void setVelocity(const Vec3<float> &vel) { _velocity = vel; }
        void setGridPosition(const Vec3<float> &siz) { _scale = siz; }

        Vec3<float> getVelocity() const { return _velocity; }
        Vec3<float> getPosition() const { return _position; }
        Vec3<float> getGridPosition() const { return _scale; }
    };
}

#endif /* !__TRANSFORM_H__ */

