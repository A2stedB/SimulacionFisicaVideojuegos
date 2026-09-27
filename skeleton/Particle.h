#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "IntegrationType.h"

class Particle
{
public:
	Particle();
	Particle(Vector3D velocity,Vector3D position,Vector3D acceleration = Vector3D{0,0,0});
	~Particle();

public:
	void integrate(double t, IntegrationType integrationType);

private:
	void explicit_euler_integration(double t);
	void sympletic_euler_integration(double t);
	void verlet_integration(double t);

private:
	Vector3D velocity{};
	physx::PxTransform transform{};
	Vector3D acceleration{};
	RenderItem* renderItem{};
};

