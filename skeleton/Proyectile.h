#pragma once
#include "Particle.h"
#include "Helper.h"
class Proyectile : public Particle
{
public:
	Proyectile();
	Proyectile(physx::PxShape* shape,Camera* camera,float velocity,float acceleration,float mass,float objective_velocity,Color color);
	Proyectile(physx::PxShape* shape,Velocity velocity, Position position, Acceleration acceleration, float mass, Velocity objective_velocity, Color color);
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

