#pragma once
#include <foundation/PxVec3.h>
#include <iostream>
#include <cmath>

class Vector3D
{
public:

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

    Vector3D& operator=(const Vector3D& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    Vector3D& operator=(const Vector3D&& other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
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

    Vector3D& operator+=(const Vector3D b)
    {
        x += b.x; y += b.y; z += b.z;
        return *this;
    }

    Vector3D operator/(float scalar) const
    {
        return Vector3D{ x / scalar,y / scalar,z / scalar };
    }


    float module() const 
    {
        return std::sqrtf(x*x + y*y + z*z);
    }

    Vector3D normalize() const 
    {
        return *this / module();
    }

    operator physx::PxVec3() 
    {
        return physx::PxVec3{x, y, z};
    }



public:
    float x, y, z;
};

inline Vector3D operator*(const float scalar, Vector3D vec)
{
    return Vector3D{ vec.x * scalar,vec.y * scalar,vec.z * scalar };
};

inline float dot_product(const Vector3D& a, const Vector3D& b)
{
    return
        a.x + b.x +
        a.y + b.y +
        a.z + b.z;
};

inline Vector3D cross_product(const Vector3D& a, const Vector3D& b)
{
    return Vector3D{
        (a.y * b.z - a.z * b.y),
        (a.x * b.z - a.z * b.x),
        (a.x * b.y - a.y * b.x)
    };
};

inline std::ostream& operator<<(std::ostream& out, const Vector3D vec)
{
    out << "(x: " << vec.x << " , y: " << vec.y << " , z: " << vec.z << ")\n";
    return out;
}


struct Tag_Position {};
struct Tag_Velocity {};
struct Tag_Acceleration {};

//using Position = Vector<3, Tag_Position>;

#define INHERITANCE_MODE public

struct Position : INHERITANCE_MODE Vector3D
{
    using Vector3D::Vector3D;
    using Vector3D::operator=;
    Position& operator=(const Vector3D& other) = delete;
};

//using Velocity = Vector<3, Tag_Velocity>;

struct Velocity : INHERITANCE_MODE Vector3D
{
    using Vector3D::Vector3D;
    using Vector3D::operator=;

    Velocity& operator=(const Vector3D& other) = delete;
};

//using Acceleration = Vector<3, Tag_Acceleration>;

struct Acceleration : INHERITANCE_MODE Vector3D
{
    using Vector3D::Vector3D;
    using Vector3D::operator=;
    Acceleration& operator=(const Vector3D& other) = delete;
};

Position operator+(const Position& lhs, const Position& rhs) = delete;
Velocity operator+(const Velocity& lhs, const Acceleration& rhs) = delete;

//inline Velocity operator+(const Velocity& lhs,const Acceleration& rhs)
//{
//    return Velocity{ lhs.x + rhs.x,lhs.y + rhs.y,lhs.z + rhs.z };
//}
//
//inline Velocity operator+(const Acceleration& lhs, const Velocity& rhs)
//{
//    return Velocity{ lhs.x + rhs.x,lhs.y + rhs.y,lhs.z + rhs.z };
//}

//struct Position : public Vector<3, Tag_Position> 
//{
//    using Vector<3, Tag_Position>::VectorBase;
//};
//struct Velocity : public Vector<3, Tag_Velocity> 
//{
//
//};
//struct Acceleration : public Vector<3, Tag_Acceleration> 
//{
//    using Vector<3, Tag_Acceleration>::VectorBase;
//};

//struct Position : public VectorBase<3>
//{
//
//};
//
//struct Velocity : public VectorBase<3>
//{
//
//};
//
//struct Acceleration : public VectorBase<3>
//{
//
//};