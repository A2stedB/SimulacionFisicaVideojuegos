#pragma once
#include <vector>

class Particle;
class ParticleGenerator;

class ParticleSystem
{
public:
	ParticleSystem() = default;
	~ParticleSystem() = default;
public:
	void addGenerator(ParticleGenerator* generator);
	void update(float dt);
public:
	std::vector<Particle*> particles;
	ParticleGenerator* generator;
};

