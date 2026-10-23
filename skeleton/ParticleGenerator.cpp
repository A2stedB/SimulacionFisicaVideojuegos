#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "Distribution.h"

const int OFFSET = 10;

ParticleGenerator::ParticleGenerator(Vector3D position, ParticleModel* particle_model)
	:position(position),model(*particle_model)
{
	//model.velocity = particle_model->velocity;
	//model.color = particle_model->color;
	//model.acceleration = particle_model->acceleration;
	//this->updateTime = updateTime;
}

void ParticleGenerator::update(ParticleSystem* system,float dt) 
{
	++count;
	if (count > max) return;
	//std::cout << count << std::endl;

	Vector3D new_velocity = model.velocity;
	Vector3D new_position = this->position;

	generate_particle(&new_position,&new_velocity);
	Particle* particle = new Particle(new_velocity,new_position,Vector3D{0,model.acceleration,0}, 0.001);
	particle->renderItem->color = model.color;
	
	system->particles.push_back(particle);
}

void ParticleGenerator::setMax(int new_max)
{
	max = new_max;
}
