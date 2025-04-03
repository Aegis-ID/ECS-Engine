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

        virtual void update(float deltaTime) = 0;
        virtual void processEntities() = 0;
    };

}

/*
 * ISystem defines the interface for all systems in the ECS architecture.
 * Systems provide the logic that operates on entities with specific component combinations.
 *
 * Usage example:
 *
 * class HealthSystem : public ECS::ISystem
 * {
 * private:
 *     std::vector<std::shared_ptr<Entity>> _entities;
 *     std::shared_ptr<EntityManager> _entityManager;
 *
 * public:
 *     void initialize(std::shared_ptr<EntityManager> entityManager)
 *     {
 *         _entityManager = entityManager;
 *         // Set up signature to filter relevant entities
 *         ECS::Signature signature;
 *         signature.set(componentManager->getComponentType<HealthComponent>());
 *         _entities = _entityManager->getEntitiesWithSignature(signature);
 *     }
 *
 *     void update(float deltaTime) override
 *     {
 *         processEntities();
 *     }
 *
 *     void processEntities() override
 *     {
 *         for (auto& entity : _entities) {
 *             auto health = entity->getComponent<HealthComponent>();
 *
 *             if (health && health->getCurrentHealth() <= 0) {
 *                 // Handle entity death
 *             }
 *         }
 *     }
 * };
 */

#endif /* !__ISYSTEM_H__ */
