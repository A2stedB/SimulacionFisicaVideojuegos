#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>
#include "Distribution.h"
#include "Particle.h"

 struct ParticleModel 
 {
 	Vector3D velocity;
 	physx::PxVec4 color;
 };

class ParticleSystem;

class ParticleGenerator
{
public:
	ParticleGenerator() = default;
	ParticleGenerator(Vector3D position, ParticleModel model);
	~ParticleGenerator() = default;

public:
	void update(ParticleSystem* system,float dt);
public:
	ParticleModel model{};
	//Distribution distribution{};
	Vector3D position{};
	const int max{10000};
	int count{ 0 };
};

