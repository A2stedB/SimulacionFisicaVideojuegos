#pragma once
#include "Particle.h"
#include "Unit.h"

class Proyectile : public Particle
{
public:
	Proyectile();
	Proyectile(Camera* camera,float velocity,ms_t acceleration,float mass,float objective_velocity);
	Proyectile(Velocity velocity, Position position, Acceleration acceleration, float mass, Velocity objective_velocity);
	~Proyectile();

	void modify_real_mass(float value); // no hace set
	void modify_real_velocity(float value);
private:
	void recalculate_simulation_mass();
	void recalculate_simulation_gravity();

private:
	float simulation_mass{};
	Velocity real_velocity{};

	Acceleration simulation_gravity{};
};

