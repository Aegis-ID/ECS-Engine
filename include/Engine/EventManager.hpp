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
        using HandlerFunction = std::function<void(const std::unique_ptr<void>)>;
        std::unordered_map<EventId, std::vector<HandlerFunction>> _handlers;
    public:
        template<typename EventType> void subscribe(std::function<void(const EventType &)>);
        template<typename EventType> void emit(EventType);
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
    void EventManager::emit(EventType event)
    {
        auto eventId = typeid(EventType).hash_code();

        if (_handlers.find(eventId) == _handlers.end())
            return;
        for (auto &handler : _handlers[eventId]) {
            auto eventPtr = std::make_unique<EventType>(std::move(event));
            handler(std::move(eventPtr));
        }
    }
}

#endif /* !__EVENTMANAGER_H__ */
