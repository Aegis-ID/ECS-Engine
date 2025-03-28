/*
** EPITECH PROJECT, 2025
** SystemManager.cpp
** File description:
** SystemManager
*/

#include "../include/SystemManager.hpp"

#include <memory>

namespace ECS 
{
    void SystemManager::addSystem(std::shared_ptr<ISystem> system)
    {
        _systems.push_back(system);
    }

    void SystemManager::update(float deltaTime) 
    {
        for (auto &system : _systems)
            system->update(deltaTime);
    }
}

