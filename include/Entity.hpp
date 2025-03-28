/*
** EPITECH PROJECT, 2025
** Entity.hpp
** File description:
** Entity
*/

#ifndef __ENTITY_H__
    #define __ENTITY_H__

    #include <cstdint>
    #include <memory>
    #include <typeindex>
    #include <unordered_map>

    #include "ComponentWrapper.hpp"

namespace ECS
{
    using EntityID = uint64_t;

    class Entity
    {
    private:
        EntityID _id;
        std::unordered_map<std::type_index, std::shared_ptr<IComponentWrapper>> _components;
    public:
        Entity() = default;
        ~Entity() = default;

        template<typename T> void addComponent();
        template<typename T> void removeComponent();        
        template<typename T> std::shared_ptr<T> getComponent();
    };
}

// Exemple d'utilisation: 
//
// auto player = std::make_shared<Entity>();
//
// grâce aux templates
// pour add/get un component vous renseignez juste le type avec <>
//
// player->addComponent<ECS::Components::PositionComponent>();
//
// auto position = player->getComponent<ECS::Components::PositionComponent>();
//
// if (position)
//     position->setPosition(5.0f, 10.0f, 0.0f);
//
//
// Vous gérez vos entités comme vous voulez, on display des entités
// on a pas besoin d'avoir en commun dont on les gère

#endif /* !__ENTITY_H__ */
