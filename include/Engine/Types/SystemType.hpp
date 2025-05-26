/*
** EPITECH PROJECT, 2025
** SystemType.hpp
** File description:
** SystemType
*/

#ifndef SYSTEMTYPE_HPP_
    #define SYSTEMTYPE_HPP_

    #include "ECS/Entity.hpp"
    #include <any>
    #include <string>
    #include <unordered_map>

namespace Engine::System
{
    enum SystemType
    {
        RENDERING,      // Systems that handle rendering entities
        UNKNOWN         // explooore the unknown
    };

    static constexpr std::string SystemTypeNames[] =
    {
        "rendering",
        "unknown"
    };

    inline constexpr std::string getSystemTypeName(SystemType type)
    {
        if (type < SystemType::RENDERING || type >= SystemType::UNKNOWN)
            return SystemTypeNames[SystemType::UNKNOWN].c_str();
        return SystemTypeNames[type].c_str();
    }

    typedef std::unordered_map<std::string, std::any> SystemConfig;
}

#endif /* !SYSTEMTYPE_HPP_ */
