#include "Particle.h"
#include "Config.h"
#include "Helper.h"
#include <iostream>
#include <cmath>

Particle::Particle(physx::PxTransform transform)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->transform = transform;

	this->renderItem = new RenderItem(shape, &this->transform, YELLOW);
}

Particle::Particle(Velocity velocity, Position position,Acceleration acceleration)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->transform = physx::PxTransform((Vector3D)position);

	this->renderItem = new RenderItem(shape,&this->transform,YELLOW);
}

Particle::Particle(Velocity velocity, Position position, Acceleration acceleration, float mass)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->transform = physx::PxTransform((Vector3D)position);
	this->mass = mass;

	this->renderItem = new RenderItem(shape, &this->transform, BLUE);
}

Particle::~Particle()
{
	delete renderItem;
}

Particle::Particle(const Particle& other)
	: velocity(other.velocity), transform(other.transform), acceleration(other.acceleration),mass{ other.mass }
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));

	this->renderItem = new RenderItem(shape, &this->transform, RED);
}

void Particle::integrate(double t, IntegrationType integrationType)
{
	switch (integrationType)
	{
	    case IntegrationType::Euler:
			explicit_euler_integration(t);
			break;
		case IntegrationType::Symplectic_Euler:
			sympletic_euler_integration(t);
			break;
		case IntegrationType::Verlet:
			verlet_integration(t);
			break;
		default:
			break;
	}
}

// t sera el tiempo de paso de fisica, constante
void Particle::explicit_euler_integration(double t)
{
	transform.p = transform.p + (velocity * FixedTimestep);
	velocity = velocity + (acceleration * FixedTimestep);

	//std::cout << velocity << std::endl;

	// No actua tanto a nivel conceptual de la fisica, sino que sirve para mantener el integrador funcionando matematicamente constante
	// El integrador produce error, ya sea positivo o negativo, pero la cosa es que ese error va acumulando
	velocity = velocity * std::pow(DAMPING_FACTOR, t);
}

void Particle::sympletic_euler_integration(double t)
{
	velocity = velocity + acceleration * FixedTimestep;
	transform.p = transform.p + (Vector3D)(velocity * FixedTimestep);

	velocity = velocity * std::pow(DAMPING_FACTOR, t);
}

void Particle::verlet_integration(double t)
{
	// TODO
	//algo(this->acceleration);
}

