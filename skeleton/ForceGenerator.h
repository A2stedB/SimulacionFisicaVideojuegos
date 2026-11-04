#pragma once
#include "Vector3D.h"
#include "Particle.h"
#include "Helper.h"
#include <PxPhysicsAPI.h>
#include <cmath>

struct BoxVolume 
{
	Position center{};
	float half_width{};
	float half_height{};
	float half_depth{};
    
	bool IsInside(Constant<Position>& position) 
	{
		return 
			(center.x - half_width < position.x && center.x + half_width > position.x) &&
			(center.y - half_height < position.y && center.y + half_height > position.y) &&
			(center.z - half_depth < position.z && center.z + half_depth > position.z);
	}
};

class ForceGenerator
{
public:
	ForceGenerator();
	~ForceGenerator() = default;
	virtual Force AddForce(Particle& particula)
	{
		return Force();
	}

public:
	// Una fuerza
	// Vector3D acceleration{};
	// Area de efecto (puede no tenerlo)
	// 
};


class GravityForceGenerator : public ForceGenerator 
{
public:
	GravityForceGenerator() = default;

	Force AddForce(Particle& particle) override
	{
		return (Force)(acceleration * particle.mass);
	}
public:
	
	Acceleration acceleration{ 0,-9.8,0 };
};


class WindForceGenerator : public ForceGenerator 
{
public:
	WindForceGenerator(Velocity wind_velocity,BoxVolume effect_volume) : wind_velocity(wind_velocity),effect_volume(effect_volume) 
	{
		center = physx::PxTransform(effect_volume.center);
		physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(effect_volume.half_width, effect_volume.half_height, effect_volume.half_depth));

		if (shape)
		{
			// Marcamos la forma como TRIGGER para que se dibuje en modo líneas / wireframe
			shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
			shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
			wireframe = new RenderItem(shape, &center,Color(0,0,0,1));
		}
	};

	~WindForceGenerator()
	{
		delete wireframe;
	}

	Force AddForce(Particle& particle) override
	{
		if (!effect_volume.IsInside(particle.transform.p))
		{
			return Force();
		}
		Constant<float> k1 = 1;
		Constant<float> k2 = 0;

		Vector3D difference = wind_velocity - particle.velocity;

		return (Force) ( k1*(difference) + 
			             k2 * difference.module() * difference);
	}

protected:
	RenderItem* wireframe;
	Velocity wind_velocity;
	BoxVolume effect_volume;
	physx::PxTransform center;
};

class WhirlwindForceGenerator : public WindForceGenerator
{
public:
	WhirlwindForceGenerator(BoxVolume effect_volume) : WindForceGenerator(Velocity(), effect_volume) {};

	Force AddForce(Particle& particle) override
	{
		if (!effect_volume.IsInside(particle.transform.p))
		{
			std::cout << "fuera" << std::endl;
			return Force();
		}

		Constant<Position>& particle_position = particle.transform.p;
		Constant<Position>& center_position = center.p;

		Constant<int> K = 10;

		Velocity whirl_velocity = (Velocity)(K * Vector3D(-(particle_position.z - center_position.z),
			50 - (particle_position.y - center_position.y),
			particle_position.x - center_position.x));

		Vector3D difference = whirl_velocity - particle.velocity;

		return (Force)(difference);
	}
};

class ExplosiveForceGenerator : public ForceGenerator
{
public:
	ExplosiveForceGenerator(Position center, float radius, float explosion_intensity,float explosion_time_constant) :
		center(center), explosion_radius(radius), explotion_intensity(explosion_intensity), explosion_time_constant(explosion_time_constant)
	{
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(3.0f));
		transform = physx::PxTransform(center);

		center_mark = new RenderItem(shape, &transform, Color(1, 0, 0, 1));
	};

	Force AddForceExplosive(Particle& particle,float dt)
	{
		Constant<Position>& particle_position = particle.transform.p;

		Constant<float> distance_x = particle_position.x - center.x;
		Constant<float> distance_y = particle_position.y - center.y;
		Constant<float> distance_z = particle_position.z - center.z;

		Constant<float> distance_to_explosion = std::sqrtf(std::powf(distance_x,2) + std::powf(distance_y, 2) + std::powf(distance_z, 2));

		if (distance_to_explosion > explosion_radius)
		{
			return Force();
		}

		Constant<float> E = 2.71828182845904523536;

		Constant<float> K_r2 = explotion_intensity / std::powf(distance_to_explosion, 2);
		Constant<float> e_tr = std::powf(E, -(dt / explosion_time_constant));

		return (Force)(K_r2 * Force(distance_x, distance_y, distance_z) * e_tr);
	}

private:

	Position center{};
	physx::PxTransform transform;
	float explosion_radius{};
	float explotion_intensity{};
	float explosion_time_constant{};
	RenderItem* center_mark = nullptr;
	//double explosion_start_time{};

};





