#pragma once
#include <foundation/PxVec3.h>
#include <cmath>

class Vector3D
{
public:
    Vector3D normalize();
    float module();

    Vector3D() : x{ 0 }, y{ 0 }, z{ 0 } {};
    Vector3D(float x,float y, float z):x{ x }, y{ y }, z{ z } {};
    Vector3D(const physx::PxVec3 pxVec3) : x{ pxVec3.x }, y{ pxVec3.y }, z{ pxVec3.z } {};

    Vector3D(const Vector3D& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3D(const Vector3D&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
    }

    Vector3D operator=(const Vector3D& other)
    {
        return Vector3D{ other.x,other.y,other.z };
    }
    Vector3D operator=(const Vector3D&& other)
    {
        return Vector3D{ other.x,other.y,other.z };
    }

    Vector3D operator*(const float scalar)
    {
        return Vector3D{ x*scalar,y*scalar,z*scalar };
    }

    Vector3D operator+(const Vector3D b) {
        return Vector3D{ x + b.x, y + b.y, z + b.z };
    }

    Vector3D operator-(const Vector3D b) {
        return Vector3D{x - b.x, y - b.y, z - b.z};
    }

    Vector3D operator+=(const Vector3D b) {
        return Vector3D{ x + b.x, y + b.y, z + b.z };
    }

    Vector3D operator/(const float scalar)
    {
        return Vector3D{ x / scalar,y / scalar,z / scalar };
    }

    float module() const 
    {
        return std::sqrtf(x*x + y*y + z*z);
    }

    Vector3D normalize() const 
    {
        return Vector3D{x,y,z} / module();
    }

    operator physx::PxVec3() {
        return physx::PxVec3{x, y, z};
    }

public:
    float x, y, z;
};

float dot_product(const Vector3D a, const Vector3D b)
{
    return 
        a.x + b.x +
        a.y + b.y +
        a.z + b.z;
}

Vector3D cross_product(const Vector3D& a, const Vector3D& b) 
{
    return Vector3D{
        (a.y*b.z - a.z*b.y),
        (a.x*b.z - a.z*b.x),
        (a.x*b.y - a.y*b.x)
    };
}

