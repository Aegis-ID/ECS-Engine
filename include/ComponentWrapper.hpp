/*
** EPITECH PROJECT, 2025
** ComponentWrapper.hpp
** File description:
** ComponentWrapper
** Vous pouvez voir ce concept sous 2 noms, Wrapper ou Decorator
** refactoring guru en parle, j'ai mis un lien juste en dessous :
** https://refactoring.guru/design-patterns/decorator
*/

#ifndef __COMPONENTWRAPPER_H__
    #define __COMPONENTWRAPPER_H__

#include <memory>

namespace ECS
{
    class IComponentWrapper
    {
    public:
        virtual ~IComponentWrapper() = default;
    };

    template <typename T> class ComponentWrapper : public IComponentWrapper
    {
    public:
        std::shared_ptr<T> _component;

        ComponentWrapper() : _component(std::make_shared<T>()) {}
        // Si vos components ont un constructor qui nécessitent des paramètres
        // bah force à vous, j'ai la flemme d'utiliser des va_list
        // modifiez vos membres à travers vos méthodes...
    };
}

// Au lieu d'être des racistes, et d'utiliser des std::any 
// (qui n'est pas opti en plus d'être raciste) ou encore
// de faire une interface vide (vide car les components n'ont rien
// en commun à par la façon dont on les utilise)
// On utilise un wrapper !

#endif /* !__COMPONENTWRAPPER_H__ */
