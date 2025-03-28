/*
** EPITECH PROJECT, 2025
** Grid.hpp
** File description:
** Grid
*/

#ifndef __GRID_H__
    #define __GRID_H__

#include "../ComponentWrapper.hpp"
#include "../Vector.hpp"

namespace ECS::Components
{
    class GridPositionComponent : public IComponentWrapper
    {
    private:
       Vec2<int> _gridPosition;
    public:
       void setGridPosition(const Vec2<int> &pos) { _gridPosition = pos; }
       Vec2<int> getGridPosition() const { return _gridPosition; }
    };
}

#endif /* !__GRID_H__ */
