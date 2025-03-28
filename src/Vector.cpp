/*
** EPITECH PROJECT, 2025
** vector.cpp
** File description:
** vector
*/

#include <cmath>
#include "../include/Vector.hpp"

// Vec2

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

// Vec3

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
