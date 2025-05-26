/*
** EPITECH PROJECT, 2025
** IComponentPool.hpp
** File description:
** IComponentPool
*/

#ifndef __ICOMPONENTPOOL_H__
    #define __ICOMPONENTPOOL_H__

    #include <memory>
    #include <queue>
    #include <vector>

namespace ECS
{
    using ComponentID = std::size_t;

    class IComponentPool
    {
    public:
        virtual ~IComponentPool() = default;
    };

    template<typename T> class ComponentPool : public IComponentPool
    {
    private:
        std::vector<std::unique_ptr<T>> _components;
        std::vector<bool> _activeComponents;
        std::queue<ComponentID> _freeIndices;
    public:
        ComponentID create();
        template<typename... Args> ComponentID create(Args&&... args);
        void destroy(ComponentID id);
        std::vector<ComponentID> getAllActiveIndices();
        T *getComponentWithIndex(ComponentID id);
    };

    template<typename T> ComponentID ComponentPool<T>::create()
    {
        ComponentID id;

        if (!_freeIndices.empty()) {
            id = _freeIndices.front();
            _freeIndices.pop();
            _components[id] = std::make_unique<T>();
        } else {
            id = _components.size();
            _components.push_back(std::make_unique<T>());
            _activeComponents.push_back(true);
        }
        _activeComponents[id] = true;
        return id;
    }

    template<typename T>
    template<typename... Args>
    ComponentID ComponentPool<T>::create(Args&&... args)
    {
        ComponentID id;

        if (!_freeIndices.empty()) {
            id = _freeIndices.front();
            _freeIndices.pop();
            _components[id] = std::make_unique<T>(std::forward<Args>(args)...);
        } else {
            id = _components.size();
            _components.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            _activeComponents.push_back(true);
        }
        _activeComponents[id] = true;
        return id;
    }

    template<typename T> void ComponentPool<T>::destroy(ComponentID id)
    {
        if (id >= _components.size() || !_activeComponents[id])
            return;
        _activeComponents[id] = false;
        _freeIndices.push(id);
    }

    template<typename T> std::vector<ComponentID> ComponentPool<T>::getAllActiveIndices()
    {
        std::vector<std::shared_ptr<T>> activeComponents;

        for (ComponentID i = 0; i < _components.size(); ++i)
            if (_activeComponents[i])
                activeComponents.push_back(_components[i]);
        return activeComponents;
    }

    template<typename T>
    T *ComponentPool<T>::getComponentWithIndex(ComponentID id)
    {
        if (id >= _components.size() || !_activeComponents[id])
            return nullptr;
        return _components[id].get();
    }
}

#endif /* !__ICOMPONENTPOOL_H__ */
