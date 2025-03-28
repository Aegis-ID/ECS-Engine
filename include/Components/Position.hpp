/*
** EPITECH PROJECT, 2025
** Position.hpp
** File description:
** Position
*/

#ifndef __POSITION_H__
    #define __POSITION_H__

    #include "../Vector.hpp"
    #include "../ComponentWrapper.hpp"

namespace ECS::Components
{
    class PositionComponent : IComponentWrapper
    {
    private:
        Vec3<float> _position;
    public:
        void setPosition(const Vec3<float> &pos) { _position = pos; }
        Vec3<float> getPosition() const { return _position; }
    };
}

#endif /* !__POSITION_H__ */
