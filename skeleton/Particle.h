#pragma once
#include "Vector3D.h"
#include "PxPhysicsAPI.h"
#include "RenderUtils.hpp"
#include "IntegrationType.h"

class Particle
{
public:
	Particle(){};
	Particle(Vector3D velocity,physx::PxTransform position){};
	~Particle(){};

public:
	void integrate(double t, IntegrationType integrationType){};

private:

private:
	Vector3D velocity;
	physx::PxTransform position;
	RenderItem* renderItem;
};

