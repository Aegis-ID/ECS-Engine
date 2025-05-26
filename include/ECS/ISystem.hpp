/*
** EPITECH PROJECT, 2025
** ISystem.hpp
** File description:
** ISystem
*/

#ifndef __ISYSTEM_H__
    #define __ISYSTEM_H__

namespace ECS
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;

        virtual void update(float deltaTime) = 0;
        virtual void processEntities() = 0;
    };

}

#endif /* !__ISYSTEM_H__ */
