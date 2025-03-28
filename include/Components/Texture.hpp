/*
** EPITECH PROJECT, 2025
** Texture.hpp
** File description:
** Texture
*/

#ifndef __TEXTURE_H__
    #define __TEXTURE_H__

    #include <string>
    #include "../ComponentWrapper.hpp"
    #include "../Vector.hpp"

namespace ECS::Components
{
    using Color = std::tuple<short, short, short, short>;

    class TextureComponent : IComponentWrapper
    {
    private:
        std::string _texturePath;
        Color _color;
        Vec2<float> _scale;
        float _rotation;
    public:
        void setTexturePath(const std::string &);
        void setColor(Color);
        void setScale(float x, float y);
        void setRotation(float);

        const std::string &getTexturePath() const;
        Color getColor() const;
        Vec2<float> getScale() const;
        float getRotation() const;
    };
}

#endif /* !__TEXTURE_H__ */
