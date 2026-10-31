#pragma once
#include "Vector3D.h"

struct BoxVolume 
{
	Position position{};

	struct {
		float width;
		float length;
	} area;

	float depth{}; // Y si es infinito?

	Normal normal{};

	bool placeholder(Position position) 
	{

	}
};

struct CylinderVolume 
{
	Position position{};
	Normal normal{};
	float radius{};
	float depth = 0;
};

//struct Volume {
//	union {
//		BoxVolume box;
//		CylinderVolume cylinder;
//	} volume;
//};

class ForceGenerator
{
public:
	ForceGenerator();

	virtual Force getForce(Particle& particula) = 0;

	virtual bool positionCheck()
	{
		return true;
	}
public:
	// Una fuerza
	//Vector3D acceleration{};
	// Area de efecto (puede no tenerlo)
	// 
};


class GravityForceGenerator : public ForceGenerator 
{
public:
	GravityForceGenerator() = default;

	Force getForce(Particle& particle) override
	{
		return (Force)(particle.acceleration * particle.mass);
	}
public:
	
	Acceleration acceleration{ 0,-9.8,0 };
};


class WindForceGenerator : public ForceGenerator 
{
public:
	WindForceGenerator(Velocity wind_velocity);

	Force getForce(Particle& particle) override
	{
		int k1 = 1;
		int k2 = 0;

		Vector3D difference = wind_velocity - particle.velocity;

		return (Force) ( k1*(difference) + 
			             k2 * difference.module() * difference);
	}

private:
	Velocity wind_velocity;
	BoxVolume effect_volume;
};



