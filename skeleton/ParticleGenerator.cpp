#include "ParticleGenerator.h"
#include "ParticleSystem.h"

ParticleGenerator::ParticleGenerator(Vector3D position, ParticleModel model)
	: model(model), position(position)
{
}

void ParticleGenerator::update(ParticleSystem* system,float dt) 
{
	++count;
	if (count > max) return;

	Particle* particle = new Particle(model.velocity,this->position,Vector3D{0,-10,0},0.001);
	
	system->particles.push_back(particle);
}
