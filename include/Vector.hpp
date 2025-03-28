/*
** EPITECH PROJECT, 2025
** vector.hpp
** File description:
** vector
*/

#ifndef __VECTOR_H__
    #define __VECTOR_H__

template <typename T> struct Vec2 {
    T x, y;

    Vec2();
    Vec2(T x_val, T y_val);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(T scalar) const;

    T dot(const Vec2 &other) const;
    T magnitude() const;
    Vec2 normalize() const;
};

template <typename T> struct Vec3 {
    T x, y, z;

    Vec3();
    Vec3(T x, T y, T z_);

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(T scalar) const;

    T dot(const Vec3 &other) const;
    Vec3 cross(const Vec3 &other) const;
    T magnitude() const;
    Vec3 normalize() const;
};

#endif /* !__VECTOR_H__ */
