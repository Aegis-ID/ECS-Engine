/*
** EPITECH PROJECT, 2025
** raytracer-mirror [WSL: Arch]
** File description:
** Name
*/

#ifndef ENITYINFO_HPP_
    #define ENITYINFO_HPP_

    #include "Engine/Types.hpp"
    #include <string>

namespace Engine::CoreComponents
{
    struct EntityInfo
    {
        std::string name;
        Entity::EntityType entityType;
        System::SystemType systemType;

        EntityInfo(){};
        EntityInfo(const std::string &name = "", Entity::EntityType entityType = Entity::EntityType::UNKNOWN,
            System::SystemType systemType = System::SystemType::UNKNOWN)
            :   name(name), entityType(entityType), systemType(systemType){}
    };
}

#endif /* !ENITYINFO_HPP_ */
