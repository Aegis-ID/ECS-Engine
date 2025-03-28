/*
** EPITECH PROJECT, 2025
** ISystem.hpp
** File description:
** ISystem
*/

#ifndef __ISYSTEM_H__
    #define __ISYSTEM_H__

namespace ECS
{
    class ISystem
    {
    public:
        virtual ~ISystem() = default;
        
        virtual void update(float deltaTime) = 0;   // 
        virtual void processEntities() = 0;
    };

}

// Les systèmes n'est autre qu'une façon de gérer les entités dans votre jeu
// Vous n'êtes pas obligé de faire ça, vous pouvez gérer comme vous le souhaitez
// mais ça rendra vos vies plus simples

// Exemple d'utilisation :
//
// Imaginons que l'on souhaite implémenter un système où l'on gère la vie de nos entités
//
// class HealthSystem : public ISystem 
// {
// private:
//     // on renseigne une liste d'entités concernées (nottament ceux qui possède les composants
//     // concernés... ou blc et vous parcourez vos 42k entities)
//     std::vector<std::shared_ptr<Entity>> entities; 
// public:
//     // une fonction update dans laquelle vous faîtes ce que vous voulez 
//     void update(float deltaTime) override
//     {
//         processEntities();
//     }
//
//     // Une fonction qui gère les entités dans laquelle vous faîtes ce que vous voulez
//     void processEntities() override
//     {
//         for (auto &entity : entities) {
//             // on accède aux components qu'on veut des entités afin de créer le système
//             auto health = entity->getComponent<ECS::Components::HealthComponent>(); 
//
//             // on applique la logique que l'on veut une fois que vous choppez ce que vous voulez
//             if (health && health->getHealth() <= 0)
//                 std::cout << "Dîtes à ma femme que je... att j'ai une femme?'" << std::endl;
//         }
//     }
// };

// Dans le cas où vous avez plusieurs systèmes, aka un JEU
// vous pouvez créer un SystemManager si vous le souhaitez
// qui permettra de mettre à jour tous les systems de votre
// jeu

#endif /* !__ISYSTEM_H__ */

