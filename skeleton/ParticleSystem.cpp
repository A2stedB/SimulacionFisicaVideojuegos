#include "ParticleSystem.h"
#include "Particle.h"
#include "IntegrationType.h"
#include "Config.h"
#include "ParticleGenerator.h"
#include <utility>
#include <algorithm>

void ParticleSystem::ResetForce()
{
	for (Force& force : particle_force)
	{
		force = Force();
	}
}

void ParticleSystem::addGenerator(ParticleGenerator* generator)
{
	generators.push_back(generator);
}

void ParticleSystem::update(float dt)
{
	for (ParticleGenerator* generator : generators)
	{
		generator->update(this, dt);
	};

	for (int i = 0; i < particles.size(); ++i)
	{
		Particle* particle = particles[i];

		particle->acceleration = particle_force[i] / particle->mass;
		particle->integrate(dt, IntegrationType::Symplectic_Euler);
		--particle->lifetime;

		if (particle->lifetime <= 0)
		{
			std::swap(particle, particles[particles.size() - 1]);
			delete particle;
			particles.pop_back();
		}
	}

	//for (Particle* particle : particles) 
	//{
	//	particle->integrate(dt,IntegrationType::Symplectic_Euler);
	//	--particle->lifetime;
	//	
	//	if (particle->lifetime <= 0)
	//	{
	//		std::swap(particle,particles[particles.size()-1]);
	//		delete particle;
	//		particles.pop_back();
	//	}
	//}
}

void ParticleSystem::PreCompute()
{
	long total_size = 0;
	for (ParticleGenerator* generator : generators)
	{
		total_size += generator->max;
	}

	particles.reserve(total_size);
	particle_force.reserve(total_size);
}
