/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** CoreComponents
*/

#ifndef CORECOMPONENTS_HPP_
    #define CORECOMPONENTS_HPP_

    #include "Engine/Types/EntityType.hpp"

    #include "Engine/Components/Position.hpp"
    #include "Engine/Components/Scale.hpp"
    #include "Engine/Components/Rotation.hpp"
    #include "Engine/Components/Color.hpp"
    #include "Engine/Components/Material.hpp"
    #include "Engine/Components/Fov.hpp"
    #include "Engine/Components/Viewport.hpp"
    #include "Engine/Components/EntityInfo.hpp"
    #include "Engine/Components/Radius.hpp"

namespace Engine::Entity
{
    inline bool checkCameraCores(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;      // -> MANDATORY COMPONENT TO EVERY TYPES
        if (!entity->getComponent<CoreComponents::Viewport>()) return false;
        if (!entity->getComponent<CoreComponents::Position>()) return false;
        if (!entity->getComponent<CoreComponents::Rotation>()) return false;
        if (!entity->getComponent<CoreComponents::Fov>()) return false;
        return true;
    }

    inline bool checkPrimitiveCores(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        if (!entity->getComponent<CoreComponents::Position>()) return false;
        if (!entity->getComponent<CoreComponents::Rotation>()) return false;
        if (!entity->getComponent<CoreComponents::Scale>()) return false;
        return true;
    }

    inline bool checkLightCores(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        if (!entity->getComponent<CoreComponents::Position>()) return false;
        return true;
    }

    inline bool checkMaterialCores(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        return true;
    }

    inline bool checkEffectCores(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        return true;
    }

    inline bool checkEntityCoreComponents(const std::shared_ptr<ECS::Entity> entity)
    {
        if (!entity) return false;
        if (!entity->getComponent<CoreComponents::EntityInfo>()) return false;
        EntityType type = entity->getComponent<CoreComponents::EntityInfo>()->entityType;
        switch (type) {
            case EntityType::CAMERA: return checkCameraCores(entity);
            case PRIMITIVE: return checkPrimitiveCores(entity);
            case LIGHT: return checkLightCores(entity);
            case MATERIAL: return checkMaterialCores(entity);
            case EFFECT: return checkEffectCores(entity);
            // insert new checkers here...
            case UNKNOWN: break;
            }
        return false;
    }
}

#endif /* !CORECOMPONENTS_HPP_ */
