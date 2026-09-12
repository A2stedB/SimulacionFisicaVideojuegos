#pragma once
template<typename T>
struct Vector3D
{
    T x, y, z;

    Vector3D normalize();
    float module();

    Vector3D() : x{ 0 }, y{ 0 }, z{ 0 } {};
    Vector3D(T x,T y, T z):x{ x }, y{ y }, z{ z } {};

    Vector3D operator=(const Vector3D& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }
    Vector3D operator=(const Vector3D&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    Vector3D operator*(const int scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
};

template<typename T>
float dot_product(const Vector3D<T>& a, const Vector3D<T>& b)
{
    return 
        a.x + b.x +
        a.y + b.y +
        a.z + b.z;
}

