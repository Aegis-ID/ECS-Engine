/*
** EPITECH PROJECT, 2025
** Health.hpp
** File description:
** Health
*/

#ifndef __HEALTH_H__
    #define __HEALTH_H__

    #include "../ComponentWrapper.hpp"

namespace ECS::Components
{
    class HealthComponent : IComponentWrapper
    {
    private:
    	float _currentHealth;
    	float _maxHealth;
    public: 
    	void takeDamage(float);
    	void heal(float);
    	bool getState();
    };
}

#endif /* !__HEALTH_H__ */
