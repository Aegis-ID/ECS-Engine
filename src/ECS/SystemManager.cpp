/*
** EPITECH PROJECT, 2025
** SystemManager.cpp
** File description:
** SystemManager
*/

#include "ECS/SystemManager.hpp"
#include "ECS/ISystem.hpp"

namespace ECS
{
    void SystemManager::addSystem(std::unique_ptr<ISystem> system)
    {
        ISystem *systemPtr = system.get();
        _systems.push_back(std::move(system));

        const std::type_info &type = typeid(*systemPtr);
        _systemMap[std::type_index(type)] = systemPtr;
    }

    void SystemManager::update(float deltaTime)
    {
        for (auto &system : _systems)
            system->update(deltaTime);
    }
}
