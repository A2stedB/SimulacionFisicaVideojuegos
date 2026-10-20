#pragma once
#include "Vector3D.h"
#include <PxPhysicsAPI.h>
#include "Distribution.h"
#include "Particle.h"



class ParticleSystem;

class ParticleGenerator
{
public:
	ParticleGenerator() = default;
	ParticleGenerator(Vector3D position, ParticleModel* particle_model);
	~ParticleGenerator() = default;

public:
	void update(ParticleSystem* system,float dt);
public:
	ParticleModel model{};
	Vector3D position{};
	const int max{10000};
	int count{ 0 };
};

