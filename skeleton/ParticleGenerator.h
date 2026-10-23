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
	//ParticleGenerator(Vector3D position, ParticleModel* particle_model);
	~ParticleGenerator() = default;

public:
	void update(ParticleSystem* system,float dt);
	void setMax(int new_max);
public:
	float (*updateTime)(ParticleGenerator*);
	void (*generate_particle)(Vector3D*,Vector3D*);
	float current_tick{ 0 };
	ParticleModel model{};
	Vector3D position{};
	int max{10000};
	int count{ 0 };
};

