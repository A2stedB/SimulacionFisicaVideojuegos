#pragma once

constexpr double FixedTimestep = 1.0f / 60.0f;

constexpr float DAMPING_FACTOR = 0.99f;

enum class IntegrationType
{
	Euler = 1,
	Symplectic_Euler,
	Verlet
};

//template<typename Type>
//struct Pointer
//{
//	Pointer() : pointer(nullptr) {};
//
//	Pointer(Type* pointer) : pointer(pointer) {};
//
//	Pointer(const Pointer& other) : pointer(other->pointer) {};
//	Pointer(const Pointer&& other) : pointer(other->pointer) {};
//
//	operator Type* () const
//	{
//		return pointer;
//	}
//
//	Type* operator->() const
//	{
//		return pointer;
//	}
//
//	Type& operator*()
//	{
//		return *pointer;
//	}
//
//private:
//	Type* pointer = nullptr;
//};

template<typename Type>
using Pointer = Type*;
