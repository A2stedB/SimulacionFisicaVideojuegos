#pragma once
#include "Vector3D.h"
#include "Particle.h"



class ParticleSystem;

using Max = int;

class ParticleGenerator
{
public:
	ParticleGenerator() = default;
	ParticleGenerator(Position position, ParticleModel particle_model,Max max);
	//ParticleGenerator(Vector3D position, ParticleModel* particle_model);
	~ParticleGenerator() = default;

public:
	void update(ParticleSystem* system,float dt);
	void Toggle()
	{
		is_active = !is_active;
	}
	//void setMax(int new_max);

public:
	float time_since_last_generation = 0;
	float (*updateTime)(ParticleGenerator*);
	void (*generate_particle)(Vector3D*,Vector3D*,int*);
	float next_generation_time = 0;
	void (*random_generation_interval)(float*) = nullptr;
	ParticleModel model{};
	Position position{};
	int max{100};
	int count{ 0 };
	bool is_active = true;
};

