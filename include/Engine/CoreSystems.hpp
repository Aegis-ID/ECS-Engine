/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** CoreSystems
*/

#ifndef CORESYSTEMS_HPP_
    #define CORESYSTEMS_HPP_

    #include "Engine/CoreComponents.hpp"
    #include "Engine/Types/SystemType.hpp"

namespace Engine::System
{
    inline bool checkRendering(const std::shared_ptr<ECS::Entity> entity)
    {
        (void)entity;
        return true;
    }

    inline bool checkSystemCoreComponents(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        SystemType type = entity->getComponent<CoreComponents::EntityInfo>()->systemType;
        switch (type) {
            case RENDERING: return checkRendering(entity);
            // insert new checkers here...
            case UNKNOWN: break;
            }
        return false;
    }
}

#endif /* !CORESYSTEMS_HPP_ */
