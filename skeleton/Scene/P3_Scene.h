#pragma once
#include "Scene.h"
#include "Particle.h"
#include "ForceGenerator.h"
#include "Helper.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        shape = CreateShape(physx::PxSphereGeometry(1.0f));
        particle = new Particle(shape,Velocity(0, 1, 0), Position{ 1.0,0.0,0.0 }, Acceleration{ 0,0,0 }, Color{0,1,0,1},10);
        gravityGenerator = new GravityForceGenerator();

        BoxVolume box = BoxVolume{ Position(0,0,0),100,20,100};

        //wind = new WindForceGenerator(Velocity(0, 1000, 0),box);
        whirl = new WhirlwindForceGenerator(box);
    }

    void update(double dt) override
    {
        particleForce = Force(0, 0, 0);
        particleForce += gravityGenerator->AddForce(*particle);
        particleForce += whirl->AddForce(*particle);

        particle->acceleration = particleForce / particle->mass;
        particle->integrate(dt, IntegrationType::Symplectic_Euler);
        // particleSystem.update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {

    }

    void cleanup() override
    {

    }

     
     

private:
    std::vector<Particle*> particles;
    Particle* particle = nullptr;
    Force particleForce;
    GravityForceGenerator* gravityGenerator = nullptr;
    WindForceGenerator* wind = nullptr;
    WhirlwindForceGenerator* whirl = nullptr;
    physx::PxShape* shape = nullptr;
};
