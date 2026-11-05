#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "Distribution.h"

const int OFFSET = 10;

ParticleGenerator::ParticleGenerator(Position position, ParticleModel particle_model,int max)
	:position(position),model(particle_model)
{
	this->max = max;
	//model.velocity = particle_model->velocity;
	//model.color = particle_model->color;
	//model.acceleration = particle_model->acceleration;
	//this->updateTime = updateTime;
}

void ParticleGenerator::update(ParticleSystem* system,float dt) 
{
	if (!is_active) return;
	++count;
	if (count > max) return;

	time_since_last_generation += dt;
	if (time_since_last_generation < next_generation_time) return;

	time_since_last_generation = 0;

	if (random_generation_interval != nullptr)
	{
		random_generation_interval(&next_generation_time);
	}

	Velocity new_velocity = model.velocity;
	Position new_position = this->position;
	int lifetime = model.lifetime;

	generate_particle(&new_position,&new_velocity,&lifetime);
	Particle* particle = new Particle(model.shape,new_velocity,new_position,model.acceleration,model.color,model.mass);
	particle->lifetime = lifetime;

	system->particles.push_back(particle);
	system->particle_force.push_back(Force());
}

//void ParticleGenerator::setMax(int new_max)
//{
//	max = new_max;
//}
