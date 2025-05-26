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
    #include <typeindex>
    #include <unordered_map>
    #include "ISystem.hpp"

namespace ECS
{
    class SystemManager
    {
    private:
        std::vector<std::unique_ptr<ISystem>> _systems;
        std::unordered_map<std::type_index, ISystem *> _systemMap;
    public:
        template<typename T> T* registerSystem();
        template<typename T> T* getSystem();
        void addSystem(std::unique_ptr<ISystem> system);
        void update(float deltaTime);
    };

    template<typename T> T *SystemManager::registerSystem()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_systemMap.find(typeIndex) != _systemMap.end())
            return static_cast<T *>(_systemMap[typeIndex]);
        auto system = std::make_unique<T>();
        T *systemPtr = system.get();
        _systemMap[typeIndex] = systemPtr;
        _systems.push_back(std::move(system));
        return systemPtr;
    }

    template<typename T> T *SystemManager::getSystem()
    {
        const std::type_index typeIndex = std::type_index(typeid(T));

        if (_systemMap.find(typeIndex) == _systemMap.end())
            return nullptr;
        return static_cast<T *>(_systemMap[typeIndex]);
    }
}

#endif /* !__SYSTEMMANAGER_H__ */
