#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "IntegrationType.h"
#include "Helper.h"

struct ParticleModel
{
	Velocity velocity{};
	Color color{};
	Acceleration acceleration{};
	physx::PxShape* shape{ nullptr };
};

class Particle
{
public:
	Particle() = default;
	Particle(physx::PxShape* shape,Position transform,Color color);
	Particle(physx::PxShape* shape,Velocity velocity,Position position,Acceleration acceleration, Color colour);
	Particle(physx::PxShape* shape, Velocity velocity, Position position, Acceleration acceleration, Color colour, float mass);
	//Particle(Vector3D velocity, float gravity, Vector4 colour);
	~Particle();

	Particle(const Particle& other);

public:
	void integrate(double t, IntegrationType integrationType);

protected:
	void explicit_euler_integration(double t);
	void sympletic_euler_integration(double t);
	void verlet_integration(double t);

public:
	Velocity velocity{};
	physx::PxTransform transform{};
	Acceleration acceleration{};
	RenderItem* renderItem{};
	float mass{};
};

//template<typename T>
//class Particle2{};
//
//template<>
//class Particle2<Projectile>

