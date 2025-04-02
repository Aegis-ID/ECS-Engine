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
    #include <stdexcept>

namespace ECS
{
    class IComponentPool
    {
    public:
        virtual ~IComponentPool() = default;
    };

    template<typename T> class ComponentPool : public IComponentPool
    {
    private:
        std::vector<std::shared_ptr<T>> _components;
        std::vector<bool> _activeComponents;
        std::queue<std::size_t> _freeIndices;

    public:
        std::shared_ptr<T> create();
        void destroy(std::size_t index);

        std::vector<std::shared_ptr<T>> getAllActive();
        size_t getIndex(const std::shared_ptr<T> &component);
        std::shared_ptr<T> getByIndex(size_t index);
    };

    template<typename T> std::shared_ptr<T> ComponentPool<T>::create()
    {
        std::size_t index;

        if (!_freeIndices.empty()) {
            index = _freeIndices.front();
            _freeIndices.pop();
            _components[index] = std::make_shared<T>();
        } else {
            index = _components.size();
            _components.push_back(std::make_shared<T>());
            _activeComponents.push_back(true);
        }
        _activeComponents[index] = true;
        return _components[index];
    }

    template<typename T> void ComponentPool<T>::destroy(std::size_t index)
    {
        if (index >= _components.size() || !_activeComponents[index])
            return;
        _activeComponents[index] = false;
        _freeIndices.push(index);
    }

    template<typename T> std::vector<std::shared_ptr<T>> ComponentPool<T>::getAllActive()
    {
        std::vector<std::shared_ptr<T>> activeComponents;

        for (std::size_t i = 0; i < _components.size(); ++i)
            if (_activeComponents[i])
                activeComponents.push_back(_components[i]);
        return activeComponents;
    }

    template<typename T> std::size_t ComponentPool<T>::getIndex(const std::shared_ptr<T>& component)
    {
        if (!component)
            throw std::runtime_error("Null component pointer");

        for (size_t i = 0; i < _components.size(); ++i)
            if (_components[i] == component && _activeComponents[i])
                return i;
        throw std::runtime_error("Invalid component pointer or inactive component");
    }

    template<typename T>
    std::shared_ptr<T> ComponentPool<T>::getByIndex(size_t index)
    {
        if (index >= _components.size() || !_activeComponents[index])
            return nullptr;
        return _components[index];
    }
}

/*
 * IComponentPool defines the interface for component storage pools used by the ECS.
 * ComponentPool<T> implements this interface for a specific component type T.
 *
 * Features:
 * - Smart pointer management for automatic memory cleanup
 * - Component recycling to avoid frequent allocations
 * - O(1) component retrieval by index
 *
 * Usage example:
 *
 * // Create a component pool
 * auto positionPool = std::make_shared<ECS::ComponentPool<PositionComponent>>();
 *
 * // Create a component
 * auto position = positionPool->create();
 * position->x = 100.0f;
 * position->y = 200.0f;
 *
 * // Get index for component lookup
 * size_t index = positionPool->getIndex(position);
 *
 * // Retrieve component by index
 * auto samePosition = positionPool->getByIndex(index);
 *
 * // Get all active components
 * auto allPositions = positionPool->getAllActive();
 *
 * // Destroy component when no longer needed
 * // (Usually handled automatically when shared_ptr reference count reaches zero)
 * positionPool->destroy(index);
 */

#endif /* !__ICOMPONENTPOOL_H__ */
