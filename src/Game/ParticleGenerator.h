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
	void (*generate_particle)(Position* position,Velocity* velocity);
	float current_tick{ 0 };
	ParticleModel model{};
	Position position{};
	int max{10000};
	int count{ 0 };
};

