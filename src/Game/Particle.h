#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "IntegrationType.h"

struct ParticleModel
{
	Velocity velocity{};
	physx::PxVec4 color{};
	Acceleration acceleration{};
};

class Particle
{
public:
	Particle() = default;
	Particle(physx::PxTransform transform);
	Particle(Velocity velocity, Position position, Acceleration acceleration = Acceleration{0,0,0});
	Particle(Velocity velocity, Position position, Acceleration acceleration = Acceleration{ 0,0,0 }, float mass = 0);
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

