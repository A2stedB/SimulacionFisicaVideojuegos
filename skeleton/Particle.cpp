#include "Particle.h"
#include "Config.h"
#include "Helper.h"
#include <cmath>

Particle::Particle()
{

}

Particle::Particle(Vector3D velocity, Vector3D position,Vector3D acceleration)
{
	physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->transform = physx::PxTransform(position);

	this->renderItem = new RenderItem(shape,&this->transform,YELLOW);
}

Particle::~Particle()
{
	delete renderItem;
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

void Particle::explicit_euler_integration(double t)
{
	transform.p = transform.p + (velocity * FixedTimestep);
	velocity = velocity + acceleration * FixedTimestep;
}

void Particle::sympletic_euler_integration(double t)
{
	velocity = velocity + acceleration * FixedTimestep;
	transform.p = transform.p + (velocity * FixedTimestep);
}

void Particle::verlet_integration(double t)
{

}
