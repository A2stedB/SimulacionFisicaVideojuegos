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
	this->velocity = objective_velocity * camera->getDir();
	this->acceleration = Vector3D(0.0f, acceleration, 0.0f);
	this->mass = mass;
	this->real_velocity = velocity * camera->getDir();
	recalculate_simulation_gravity();
	recalculate_simulation_mass();

	std::cout << "Masa real: " << mass << std::endl;
	std::cout << "Masa simulada: " << simulation_mass << std::endl;
}

Proyectile::Proyectile(Vector3D velocity, Vector3D position, Vector3D acceleration, float mass, Vector3D objective_velocity):
	Particle(velocity,position,acceleration,mass)
{
	this->real_velocity = velocity;
	this->velocity = objective_velocity;
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
	std::cout << "Current real mass: " << mass << "\n";
	recalculate_simulation_mass();
	std::cout << "Current simulation mass: " << simulation_mass << "\n";

	//recalculate_simulation_gravity(); // Innecesario esto
}

void Proyectile::modify_real_velocity(float value)
{
	std::cout << "Current real velocity: " << real_velocity << "\n";
	//float factor = real_velocity.module();
	//factor += value;
	//std::cout << "Factor: " << factor << std::endl;
	real_velocity.x += value;
	real_velocity.y += value;
	real_velocity.z += value;

	//real_velocity.x += value;

	recalculate_simulation_mass();
	recalculate_simulation_gravity();
	std::cout << "Current simulation velocity: " << velocity << "\n";
}

void Proyectile::recalculate_simulation_mass()
{
	const float simulation_velocity_module = velocity.module();
	const float real_velocity_module = real_velocity.module();
	simulation_mass = mass * (std::pow(real_velocity_module,2) / std::pow(simulation_velocity_module,2));
}

void Proyectile::recalculate_simulation_gravity()
{
	const float real_velocity_module = real_velocity.module();
	const float simulation_velocity_module = velocity.module();
	//const float real_gravity_module = acceleration.module();

	const float factor = this->acceleration.module() * (std::pow(simulation_velocity_module, 2) / std::pow(real_velocity_module, 2));
	simulation_gravity = this->acceleration * factor;
	this->acceleration = simulation_gravity;
}
