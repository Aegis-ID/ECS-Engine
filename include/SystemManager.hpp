/*
** EPITECH PROJECT, 2025
** SystemManager.hpp
** File description:
** SystemManager
*/

#ifndef __SYSTEMMANAGER_H__
    #define __SYSTEMMANAGER_H__

#include <memory>
#include <vector>
#include "ISystem.hpp"

namespace ECS
{
    class SystemManager 
    {
    private:
        std::vector<std::shared_ptr<ISystem>> _systems;
    public:
        void addSystem(std::shared_ptr<ISystem> system);
        void update(float deltaTime);
    };
}

#endif /* !__SYSTEMMANAGER_H__ */

