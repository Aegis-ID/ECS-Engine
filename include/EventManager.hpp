/*
** EPITECH PROJECT, 2025
** EventManager.hpp
** File description:
** EventManager
*/

#ifndef __EVENTMANAGER_H__
    #define __EVENTMANAGER_H__

    #include <cstddef>
    #include <functional>
    #include <unordered_map>
    #include <vector>
    #include <memory>

namespace ECS
{
    class EventManager
    {
    private:
        using EventId = std::size_t;
        using HandlerFunction = std::function<void(const std::shared_ptr<void>&)>;
        std::unordered_map<EventId, std::vector<HandlerFunction>> _handlers;
    public:
        template<typename EventType> void subscribe(std::function<void(const EventType &)>);
        template<typename EventType> void emit(const EventType &);
    };

    template<typename EventType>
    void EventManager::subscribe(std::function<void(const EventType &)> handler)
    {
        auto eventId = typeid(EventType).hash_code();

        auto wrappedHandler = [handler](const std::shared_ptr<void> &eventPtr) {
            handler(*std::static_pointer_cast<EventType>(eventPtr));
        };
        _handlers[eventId].push_back(wrappedHandler);
    }

    template<typename EventType>
    void EventManager::emit(const EventType &event)
    {
        auto eventId = typeid(EventType).hash_code();

        if (_handlers.find(eventId) == _handlers.end())
            return;
        auto eventPtr = std::make_shared<EventType>(event);
        for (auto &handler : _handlers[eventId])
            handler(eventPtr);
    }
}

/*
 * EventManager implements a type-safe event system using the observer pattern.
 * It allows components and systems to communicate without direct dependencies.
 *
 * Key Features:
 * - Type-safe event subscription and emission
 * - Runtime event type resolution with no inheritance required
 * - Safe event data sharing via shared pointers
 * - Support for any number of event types without modification
 *
 * Usage example:
 *
 * // Define an event
 * struct CollisionEvent {
 *     EntityID entity1;
 *     EntityID entity2;
 * };
 *
 * // Create event manager
 * ECS::EventManager eventManager;
 *
 * // Subscribe to event
 * eventManager.subscribe<CollisionEvent>([](const CollisionEvent& event) {
 *     std::cout << "Collision between " << event.entity1 << " and " << event.entity2 << std::endl;
 * });
 *
 * // Emit an event
 * CollisionEvent collision = { player->getID(), enemy->getID() };
 * eventManager.emit(collision);
 *
 * // Events are automatically cleaned up after all handlers are called
 */

#endif /* !__EVENTMANAGER_H__ */
