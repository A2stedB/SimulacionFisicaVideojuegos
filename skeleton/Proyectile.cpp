#include "Proyectile.h"
#include <cmath>
#include <iostream>
#include "Render/Camera.h"
#include <PxPhysicsAPI.h>

Proyectile::Proyectile()
{
}

Proyectile::Proyectile(Camera* camera, float velocity, float acceleration, float mass, float objective_velocity):
	Particle(physx::PxTransform(camera->getEye()))
{
	this->transform = physx::PxTransform(camera->getEye());
	this->velocity = velocity * camera->getDir();
	this->acceleration = acceleration * camera->getDir();
	this->mass = mass;
	this->simulation_velocity = objective_velocity * camera->getDir();
	recalculate_simulation_gravity();
	recalculate_simulation_mass();

	std::cout << "Masa real: " << mass << std::endl;
	std::cout << "Masa simulada: " << simulation_mass << std::endl;
}

Proyectile::Proyectile(Vector3D velocity, Vector3D position, Vector3D acceleration, float mass, Vector3D objective_velocity):
	Particle(velocity,position,acceleration,mass)
{
	simulation_velocity = objective_velocity;
	recalculate_simulation_gravity();
	recalculate_simulation_mass();

	std::cout << "Masa real: " << mass << std::endl;
	std::cout << "Masa simulada: " << simulation_mass << std::endl;
}

Proyectile::~Proyectile()
{
}

void Proyectile::modify_real_mass(float value)
{
	mass += value;
	recalculate_simulation_mass();
	//recalculate_simulation_gravity(); // Innecesario esto
}

void Proyectile::recalculate_simulation_mass()
{
	const float velocity_module = velocity.module();
	const float simulation_velocity_module = simulation_velocity.module();
	simulation_mass = mass * (std::pow(velocity_module,2) / std::pow(simulation_velocity_module,2));
}

void Proyectile::recalculate_simulation_gravity()
{
	const float velocity_module = velocity.module();
	const float simulation_velocity_module = simulation_velocity.module();
	const float real_gravity_module = acceleration.module();

	simulation_gravity = real_gravity_module * (std::pow(simulation_velocity_module, 2) / std::pow(velocity_module, 2));
}
