#pragma once
#include "PxPhysicsAPI.h"

/*
    Colors
*/

struct Vector4D
{
    Vector4D() {};
    Vector4D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    float x{}, y{}, z{}, w{};

    operator physx::PxVec4()
    {
        return physx::PxVec4{ x,y,z,w };
    }
};

using Color = Vector4D;

static Color RED = { 1.0f,0.0f,0.0f,1.0f };
static Color GREEN = { 0.0f,1.0f,0.0f,1.0f };
static Color BLUE = { 0.0f,0.0f,1.0f,1.0f };
static Color YELLOW = { 1.0f,1.0f,0.0f,1.0f };


template<typename T>
using Constant = const T;
