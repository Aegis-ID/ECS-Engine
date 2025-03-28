/*
** EPITECH PROJECT, 2025
** Motion.hpp
** File description:
** Motion
*/

#ifndef __MOTION_H__
    #define __MOTION_H__

#include "../ComponentWrapper.hpp"
#include "../Vector.hpp"

namespace ECS::Components
{
    class MotionComponent : public IComponentWrapper
    {
    private:
        Vec3<float> _position;
        Vec3<float> _velocity;
        Vec3<float> _acceleration;
    public:
        void setPosition(const Vec3<float> &pos) { _position = pos; }
        void setVelocity(const Vec3<float> &vel) { _velocity = vel; }
        void setAcceleration(const Vec3<float> &acc) { _acceleration = acc; }

        Vec3<float> getVelocity() const { return _velocity; }
        Vec3<float> getPosition() const { return _position; }
        Vec3<float> getAcceleration() const { return _acceleration; }
    };
}

#endif /* !__MOTION_H__ */

