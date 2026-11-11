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

	virtual Force AddForce(Particle& particula,float dt)
	{
		return Force();
	}

	virtual void Toggle()
	{
		is_active = !is_active;
	}
public:
	bool is_active = true;
	
};


class GravityForceGenerator : public ForceGenerator 
{
public:
	GravityForceGenerator() = default;

	Force AddForce(Particle& particle, float dt) override
	{
		if (!is_active)
		{
			return Force();
		}
		return (Force)(acceleration * particle.mass);
	}

	virtual void Toggle() override
	{
		ForceGenerator::Toggle();
		std::cout << "Generador de fuerza de gravedad: " + (std::string)(is_active ? "activado" : "desactivado") << std::endl;
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

		//if (shape)
		//{
		//	shape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
		//	shape->setFlag(physx::PxShapeFlag::eTRIGGER_SHAPE, true);
		//	wireframe = new RenderItem(shape, &center,Color(0,0,0,1));
		//}
	};

	~WindForceGenerator()
	{
		delete wireframe;
	}

	Force AddForce(Particle& particle, float dt) override
	{
		if (!is_active)
		{
			return Force();
		}

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

	virtual void Toggle() override
	{
		ForceGenerator::Toggle();
		std::cout << "Generador de fuerza de viento: " + (std::string)(is_active ? "activado" : "desactivado") << std::endl;
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

	Force AddForce(Particle& particle, float dt) override
	{
		if (!is_active)
		{
			return Force();
		}

		if (!effect_volume.IsInside(particle.transform.p))
		{
			return Force();
		}

		Constant<Position>& particle_position = particle.transform.p;
		Constant<Position>& center_position = center.p;

		Constant<int> K = 10;

		Velocity whirl_velocity = (Velocity)(Vector3D(-(particle_position.z - center_position.z),
			50-(particle_position.y - center_position.y), 
			particle_position.x - center_position.x));

		Vector3D difference = (Vector3D)whirl_velocity - (Vector3D)particle.velocity;

		return (Force)(difference);
	}

	virtual void Toggle() override
	{
		ForceGenerator::Toggle();
		std::cout << "Generador de fuerza de torbellino: " + (std::string)(is_active ? "activado" : "desactivado") << std::endl;
	}
};

class ExplosiveForceGenerator : public ForceGenerator
{
public:
	ExplosiveForceGenerator(Position center, float radius, float K,float tau) :
		center(center), explosion_radius(radius), explotion_intensity(K), explosion_time_constant(tau)
	{
		physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(3.0f));
		transform = physx::PxTransform(center);

		center_mark = new RenderItem(shape, &transform, Color(0, 0, 1, 1));
	};

	Force AddForce(Particle& particle,float dt) override
	{
		if (!is_active)
		{
			return Force();
		}

		time_since_explosion += dt;

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
		Constant<float> e_tr = std::powf(E, -(time_since_explosion / explosion_time_constant));

		return (Force)(K_r2 * Force(distance_x, distance_y, distance_z) * e_tr);
	}

	void ActiveExplosion()
	{
		if (!is_active) return;
		time_since_explosion = 0;
		std::cout << "Explosion!" << std::endl;
	}

	virtual void Toggle() override
	{
		ForceGenerator::Toggle();
		std::cout << "Generador de fuerza de explosion: " + (std::string)(is_active ? "activado" : "desactivado") << std::endl;
	}

private:
	double time_since_explosion = 0;
	Position center{};
	physx::PxTransform transform{};
	float explosion_radius{};
	float explotion_intensity{};
	float explosion_time_constant{};
	RenderItem* center_mark = nullptr;

};


class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double k, double resting_length, Particle* other) :
		k(k), resting_length(resting_length), other(other)
	{

	}



	Force AddForce(Particle& particle, float dt) override
	{
		if (&particle == other)
		{
			return Force();
		}

		Vector3D relative_position_vector = other->transform.p - particle.transform.p;
		Vector3D normalized = relative_position_vector.normalize();

		Constant<float> length = normalized.module();
		Constant<float> delta_x = length - resting_length;

		return Force(relative_position_vector * delta_x * k);
	}
protected:
	double k = 0;
	double resting_length = 0;
	Particle* other = nullptr;
};

class AnchorSpringFG : public SpringForceGenerator
{
public:
	AnchorSpringFG(double k, double resting_length, Position anchor_position) :
		SpringForceGenerator(k, resting_length, nullptr)
	{
		other = new Particle(shape, anchor_position, YELLOW);
	};

private:
	physx::PxShape* shape = CreateShape(physx::PxBoxGeometry(2, 2, 2));
};



