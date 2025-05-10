/*
** EPITECH PROJECT, 2025
** Math.hpp
** File description:
** Math
*/

#ifndef __MATH_H__
    #define __MATH_H__

    #include <cmath>

namespace Math
{
    class Vector3D
    {
    public:
        double x, y, z;
        ~Vector3D() = default;
        Vector3D()  :   x(0), y(0), z(0) {}
        Vector3D(double x, double y, double z)
            :   x(x), y(y), z(z) {}

        Vector3D operator+(const Vector3D &other) const
        {
            return Vector3D(x + other.x, y + other.y, z + other.z);
        }

        Vector3D operator-(const Vector3D &other) const
        {
            return Vector3D(x - other.x, y - other.y, z - other.z);
        }

        Vector3D operator*(const Vector3D &other) const
        {
            return Vector3D(x * other.x, y * other.y, z * other.z);
        }

        Vector3D operator*(double scalar) const
        {
            return Vector3D(x * scalar, y * scalar, z * scalar);
        }

        Vector3D operator/(const Vector3D &other) const
        {
            return Vector3D(x / other.x, y / other.y, z / other.z);
        }

        Vector3D operator/(double div) const
        {
            return Vector3D(x / div, y / div, z / div);
        }

        Vector3D &operator+=(const Vector3D &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3D &operator-=(const Vector3D &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3D &operator*=(const Vector3D &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vector3D &operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3D &operator/=(const Vector3D &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Vector3D &operator/=(double div)
        {
            x /= div;
            y /= div;
            z /= div;
            return *this;
        }

        double squareLength()
        {
            return pow(x, 2) + pow(y, 2) + pow(z, 2);
        }

        double length()
        {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        double dot(const Vector3D &other) const
        {
            return x * other.x + y + other.y + z + other.z;
        }

        double sum() const
        {
            return x + y + z;
        }
    };

    class Point3D
    {
    public:
        double x, y, z;
        ~Point3D() = default;
        Point3D()   :   x(0), y(0), z(0) {}
        Point3D(double x, double y, double z)
            :   x(x), y(y), z(z) {}

        Point3D operator+(Point3D &other) const
        {
            return Point3D(x + other.x, y + other.y, z + other.z);
        }

        Point3D operator+(Vector3D &other) const
        {
            return Point3D(x + other.x, y + other.y, z + other.z);
        }

        Point3D operator-(const Point3D &other) const
        {
            return Point3D(x - other.x, y - other.y, z - other.z);
        }

        Point3D operator*(const Point3D &other) const
        {
            return Point3D(x * other.x, y * other.y, z * other.z);
        }

        Point3D operator/(const Point3D &other) const
        {
            return Point3D(x / other.x, y / other.y, z / other.z);
        }

        Point3D operator*(double scalar) const
        {
            return Point3D(x * scalar, y * scalar, z * scalar);
        }

        Point3D operator/(double div) const
        {
            return Point3D(x / div, y / div, z / div);
        }

        Point3D &operator+=(const Point3D &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Point3D &operator+=(const Vector3D &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Point3D &operator-=(const Point3D &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Point3D &operator*=(const Point3D &other)
        {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Point3D &operator*=(double scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Point3D &operator/=(const Point3D &other)
        {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }

        Point3D &operator/=(double div)
        {
            x /= div;
            y /= div;
            z /= div;
            return *this;
        }

        double dot(const Point3D &other) const
        {
            return x * other.x + y + other.y + z + other.z;
        }

        double squareLength()
        {
            return pow(x, 2) + pow(y, 2) + pow(z, 2);
        }

        double length()
        {
            return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        }

        double sum() const
        {
            return x + y + z;
        }
    };
}

#endif /* !__MATH_H__ */

