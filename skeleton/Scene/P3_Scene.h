#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"
#include "Helper.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        particle = Particle();
    }

    void update(double dt) override
    {
        //particleSystem.update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {
    }

    void cleanup() override
    {

    }
private:
    Particle particle;
};
