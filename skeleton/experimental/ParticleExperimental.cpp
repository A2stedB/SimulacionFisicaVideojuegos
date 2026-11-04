#include <cmath>
#include "ParticleExperimental.h"
#include "../Config.h"

namespace sim
{
	void Particle_ExplicitEulerIntegration(Ref<Particle> particle, double dt);
	void Particle_SympleticEulerIntegration(Ref<Particle> particle, double dt);
	void Particle_VerletIntegration(Ref<Particle> particle, double dt);
}

sim::Particle::Particle(Position position, Velocity velocity, Acceleration acceleration):
	position(position),velocity(velocity),acceleration(acceleration)
{
}


void sim::Particle_Integrate(Ref<Particle> particle,double dt, IntegrationType integration_type)
{
	switch (integration_type)
	{
		case IntegrationType::Euler:
			Particle_ExplicitEulerIntegration(particle,dt);
			break;
		case IntegrationType::Symplectic_Euler:
			Particle_SympleticEulerIntegration(particle, dt);
			break;
		case IntegrationType::Verlet:
			Particle_VerletIntegration(particle,dt);
			break;
		default:
			throw 1;
			break;
	}
}

void Particle_ExplicitEulerIntegration(Ref<sim::Particle> particle, double dt)
{
	particle.position = particle.position+ (particle.velocity * dt);
	particle.velocity = particle.velocity + particle.acceleration * dt;

	//std::cout << velocity << std::endl;

	// No actua tanto a nivel conceptual de la fisica, sino que sirve para mantener el integrador funcionando matematicamente constante
	// El integrador produce error, ya sea positivo o negativo, pero la cosa es que ese error va acumulando
	particle.velocity = particle.velocity * std::pow(DAMPING_FACTOR, dt);
}

void Particle_SympleticEulerIntegration(Ref<sim::Particle> particle, double dt)
{
	particle.velocity = particle.velocity + particle.acceleration * dt;
	particle.position = particle.position + (particle.velocity * dt);


	particle.velocity = particle.velocity * std::pow(DAMPING_FACTOR, dt);
}

void Particle_VerletIntegration(Ref<sim::Particle> particle, double dt)
{
	// TODO
}
