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

        ParticleModel model{ Vector3D{20,0,0},RED };
        ParticleGenerator* generator = new ParticleGenerator(Vector3D{0,20,0},&model);

        particleSystem.addGenerator(generator);
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

private:
    ParticleSystem particleSystem{};
    //ParticleGenerator generator;
};
