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
    class Vec3
    {
    public:
        double x, y, z;
        Vec3() : x(0), y(0), z(0) {}
        Vec3(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}

        Vec3 operator + (const Vec3& v) const { return Vec3(x+v.x, y+v.y, z+v.z); }
        Vec3 operator - (const Vec3& v) const { return Vec3(x-v.x, y-v.y, z-v.z); }
        Vec3 operator * (double s) const { return Vec3(x*s, y*s, z*s); }
        Vec3 operator - () const { return Vec3(-x, -y, -z); }
        Vec3 operator / (double scalar) const { return Vec3(x / scalar, y / scalar, z / scalar); }

        double dot(const Vec3& v) const { return x*v.x + y*v.y + z*v.z; }

        Vec3 cross(const Vec3& v) const {
            return Vec3(
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            );
        }

        Vec3 operator * (const Vec3 &v) const {
            return Vec3(x*v.x, y*v.y, z*v.z);
        }

        Vec3& operator += (const Vec3 &v) {
            x += v.x; y += v.y; z += v.z;
            return *this;
        }

        Vec3 normalize() const {
            double len = std::sqrt(x*x + y*y + z*z);
            return Vec3(x/len, y/len, z/len);
        }
    };
}

#endif /* !__MATH_H__ */
