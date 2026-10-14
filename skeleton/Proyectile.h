#pragma once
#include "Particle.h"

class Proyectile : public Particle
{
public:
	Proyectile();
	Proyectile(Camera* camera,float velocity,float acceleration,float mass,float objective_velocity);
	Proyectile(Vector3D velocity, Vector3D position, Vector3D acceleration, float mass, Vector3D objective_velocity);
	~Proyectile();

	void modify_real_mass(float value); // no hace set
	void modify_real_velocity(float value);
private:
	void recalculate_simulation_mass();
	void recalculate_simulation_gravity();

private:
	float simulation_mass{};
	Vector3D real_velocity{};

	Vector3D simulation_gravity{};
};

