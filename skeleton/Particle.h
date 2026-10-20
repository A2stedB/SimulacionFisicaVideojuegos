#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "IntegrationType.h"

struct ParticleModel
{
	Vector3D velocity{};
	physx::PxVec4 color{};
};

class Particle
{
public:
	Particle() = default;
	Particle(physx::PxTransform transform);
	Particle(Vector3D velocity,Vector3D position,Vector3D acceleration = Vector3D{0,0,0});
	Particle(Vector3D velocity, Vector3D position, Vector3D acceleration = Vector3D{ 0,0,0 }, float mass = 0);
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
	Vector3D velocity{};
	physx::PxTransform transform{};
	Vector3D acceleration{};
	RenderItem* renderItem{};
	float mass{};
};

