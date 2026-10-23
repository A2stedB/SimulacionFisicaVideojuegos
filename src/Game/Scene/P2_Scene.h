#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"

class P2_Scene : public Scene 
{
public:
    explicit P2_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        //ParticleModel particle = Particle(Vector3D{ 10.0,0.0,0.0 }, Vector3D{ 1.0,0.0,0.0 }, Vector3D{ 0,-3,0 },0.001);

        ParticleModel model{ Velocity{20,0,0},RED,Acceleration{0,-10,0}};
        
        ParticleGenerator* generator = new ParticleGenerator(Vector3D{0,20,0},&model);
        generator->generate_particle = [](Position* position, Velocity* velocity)
            {
                int OFFSET = 20;
                velocity->x = distribution::uniform(velocity->x - OFFSET, velocity->x + OFFSET);
                velocity->y = distribution::uniform(velocity->y - OFFSET, velocity->y + OFFSET);
                velocity->z = distribution::uniform(velocity->z - OFFSET, velocity->z + OFFSET);

                position->x = distribution::uniform(position->x - OFFSET, position->x + OFFSET);
                position->y = distribution::uniform(position->y - OFFSET, position->y + OFFSET);
                position->z = distribution::uniform(position->z - OFFSET, position->z + OFFSET);
            };

        //particleSystem.addGenerator(generator);
        ParticleModel model2{ Velocity{0,-10,0},YELLOW,Acceleration{0,-10,0} };

        ParticleGenerator* generator2 = new ParticleGenerator(Vector3D{ 20,20,-10 }, &model2);
        generator2->generate_particle = [](Position* position, Velocity* velocity)
            {
                position->x = distribution::normal(position->x-50,position->x+50);
                //position->y = distribution::normal(position->y,20);
                position->z = distribution::normal(position->z-50, position->z+50);

                velocity->y = distribution::uniform(velocity->y - 5,velocity->y + 5);
            };

        //particleSystem.addGenerator(generator2);

        ParticleModel model3{ Velocity{0,20,0},BLUE,Acceleration{0,-10,0}};
        ParticleGenerator* generator3 = new ParticleGenerator(Vector3D{ 50,50,-20 }, &model3);

        generator3->generate_particle = [](Position* position, Velocity* velocity)
            {
                velocity->x = distribution::uniform(-10, 10);
            };

        particleSystem.addGenerator(generator3);
    }

    void update(double dt) override 
    {
        particleSystem.update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {
    }

    void cleanup() override 
    {

    }

private:
    ParticleSystem particleSystem{};
    //ParticleGenerator generator;
};
