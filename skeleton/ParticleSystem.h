#pragma once
#include <vector>
#include "Vector3D.h"

class Particle;
class ParticleGenerator;

class ParticleSystem
{
public:
	ParticleSystem() = default;
	~ParticleSystem() = default;
public:
	void ResetForce();
	void addGenerator(ParticleGenerator* generator);
	void update(float dt);
	void PreCompute();
public:
	std::vector<Particle*> particles;
	std::vector<Force> particle_force;
	std::vector<ParticleGenerator*> generators;
	//ParticleGenerator* generator;
};

//void CalcualteForce(ParticleSystem* particle_system,);

