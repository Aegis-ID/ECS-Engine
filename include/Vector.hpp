/*
** EPITECH PROJECT, 2025
** vector.hpp
** File description:
** vector
*/

#ifndef __VECTOR_H__
    #define __VECTOR_H__

    #include <cmath>

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

template <typename T> Vec2<T>::Vec2() : x(0), y(0) {}

template <typename T> Vec2<T>::Vec2(T x, T y) : x(x), y(y) {}

template <typename T> Vec2<T> Vec2<T>::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

template <typename T> Vec2<T> Vec2<T>::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}

template <typename T> Vec2<T> Vec2<T>::operator*(T scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

template <typename T> T Vec2<T>::dot(const Vec2 &other) const
{
    return x * other.x + y * other.y;
}

template <typename T> T Vec2<T>::magnitude() const
{
    return std::sqrt(x * x + y * y);
}

template <typename T> Vec2<T> Vec2<T>::normalize() const
{
    T mag = magnitude();
    return (mag > 0) ? Vec2(x / mag, y / mag) : Vec2(0, 0);
}

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

template <typename T> Vec3<T>::Vec3() : x(0), y(0), z(0) {}

template <typename T> Vec3<T>::Vec3(T x, T y, T z) : x(x), y(y), z(z) {}

template <typename T> Vec3<T> Vec3<T>::operator+(const Vec3 &other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

template <typename T> Vec3<T> Vec3<T>::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

template <typename T> Vec3<T> Vec3<T>::operator*(T scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}

template <typename T> T Vec3<T>::dot(const Vec3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

template <typename T> Vec3<T> Vec3<T>::cross(const Vec3 &other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

template <typename T> T Vec3<T>::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

template <typename T> Vec3<T> Vec3<T>::normalize() const
{
    T mag = magnitude();
    return (mag > 0) ? Vec3(x / mag, y / mag, z / mag) : Vec3(0, 0, 0);
}

#endif /* !__VECTOR_H__ */
