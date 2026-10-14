#include "ParticleSystem.h"
#include "Particle.h"
#include "IntegrationType.h"
#include "Config.h"
#include "ParticleGenerator.h"
void ParticleSystem::addGenerator(ParticleGenerator* generator)
{
	
}

void ParticleSystem::update(float dt)
{
	generator->update(this,dt);
	for (Particle* particle : particles) {
		particle->integrate(FixedTimestep,IntegrationType::Symplectic_Euler);
	}
}
