#include <cmath>
#include "ParticleExperimental.h"
#include "core.h"

namespace sim
{
	void Particle_Integrate_Euler(Pointer<Particle> particle, double dt);
	void Particle_Integrate_SympleticEuler(Pointer<Particle> particle, double dt);
	void Particle_Integrate_Verlet(Pointer<Particle> particle, double dt);

}

sim::Particle::Particle(Position position, Velocity velocity, Acceleration acceleration):
	position(position),velocity(velocity),acceleration(acceleration)
{
}

sim::Particle::Particle(ParticleData data):
	position(data.position),velocity(data.velocity),acceleration(data.acceleration)
{

}

sim::ParticleWithMass::ParticleWithMass(ParticleWithMassData data):
	particle(Particle(data.particle_data)),mass(data.mass)
{

}


void sim::Particle_Integrate(Pointer<Particle> particle,double dt, IntegrateType integration_type)
{
	switch (integration_type)
	{
		case IntegrateType::Euler:
			Particle_Integrate_Euler(particle,dt);
			break;
		case IntegrateType::Symplectic_Euler:
			Particle_Integrate_SympleticEuler(particle, dt);
			break;
		case IntegrateType::Verlet:
			Particle_Integrate_Verlet(particle,dt);
			break;
		default:
			throw 1;
			break;
	}
}

void sim::Particle_Integrate_Euler(Pointer<Particle> particle, double dt)
{
	particle->position = particle->position + (particle->velocity * dt);
	particle->velocity = particle->velocity + particle->acceleration * dt;

	//std::cout << velocity << std::endl;

	// No actua tanto a nivel conceptual de la fisica, sino que sirve para mantener el integrador funcionando matematicamente constante
	// El integrador produce error, ya sea positivo o negativo, pero la cosa es que ese error va acumulando
	particle->velocity = particle->velocity * std::pow(DAMPING_FACTOR, dt);
}

void sim::Particle_Integrate_SympleticEuler(Pointer<Particle> particle, double dt)
{
	particle->velocity = particle->velocity + particle->acceleration * dt;
	particle->position = particle->position + Vector3D(particle->velocity * dt);


	particle->velocity = particle->velocity * std::pow(DAMPING_FACTOR, dt);
}

void sim::Particle_Integrate_Verlet(Pointer<Particle> particle, double dt)
{
	// TODO
}
