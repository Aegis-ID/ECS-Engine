/*
** EPITECH PROJECT, 2025
** EntityType.hpp
** File description:
** EntityType
*/

#ifndef ENTITYTYPE_HPP_
    #define ENTITYTYPE_HPP_

    #include <unordered_map>
    #include <string>
    #include <any>

namespace Engine::Entity
{
    enum EntityType
    {
        CAMERA,         // -> NEVER TOUCH THIS OR ADD ANYTHING BEFORE, THIS IS HOLY
        PRIMITIVE,      // -> Basic geometric shapes like cubes, spheres
        LIGHT,          // -> Different types of lights
        MATERIAL,       // -> Define surace properties for rendered objects
        EFFECT,         // -> Post-processing effects, particle systems
        UNKNOWN         // -> NEVER TOUCH THIS OR ADD ANYTHING AFTER, THIS IS (also) HOLY
    };

    static constexpr std::string EntityTypeNames[] =
    {
        "camera",
        "primitive",
        "light",
        "material",
        "effect",
        "unknown"
    };

    inline constexpr std::string getEntityTypeName(EntityType type)
    {
        if (type < EntityType::CAMERA || type >= EntityType::UNKNOWN)
            return EntityTypeNames[EntityType::UNKNOWN].c_str();
        return EntityTypeNames[type].c_str();
    }

    typedef std::unordered_map<std::string, std::any> EntityConfig;
}

#endif /* !ENTITYTYPE_HPP_ */
