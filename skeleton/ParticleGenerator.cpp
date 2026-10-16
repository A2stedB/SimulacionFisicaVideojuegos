#include "ParticleGenerator.h"
#include "ParticleSystem.h"
#include "Distribution.h"

const int OFFSET = 10;

ParticleGenerator::ParticleGenerator(Vector3D position, ParticleModel model)
	: model(model), position(position)
{
}

void ParticleGenerator::update(ParticleSystem* system,float dt) 
{
	++count;
	if (count > max) return;
	std::cout << count << std::endl;

	Vector3D new_velocity = model.velocity;
	Vector3D new_position = this->position;

	new_velocity.x = distribution::uniform(new_velocity.x - OFFSET, new_velocity.x + OFFSET);
	new_velocity.y = distribution::uniform(new_velocity.y - OFFSET, new_velocity.y + OFFSET);
	new_velocity.z = distribution::uniform(new_velocity.z - OFFSET, new_velocity.z + OFFSET);

	new_position.x = distribution::uniform(new_position.x - OFFSET, new_position.x + OFFSET);
	new_position.y = distribution::uniform(new_position.y - OFFSET, new_position.y + OFFSET);
	new_position.z = distribution::uniform(new_position.z - OFFSET, new_position.z + OFFSET);

	Particle* particle = new Particle(new_velocity,new_position,Vector3D{0,-1,0},0.001);
	
	system->particles.push_back(particle);
}
