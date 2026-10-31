#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include "ParticleGenerator.h"
#include "Particle.h"
#include "Helper.h"
#include "ForceGenerator.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        particle = new Particle(Velocity(0,20,0), Position{1.0,0.0,0.0},Acceleration{0,0,0},10);
        gravityGenerator = new GravityForceGenerator();
    }

    void update(double dt) override
    {
        particleForce = gravityGenerator->getForce(*particle);
        particle->acceleration = particleForce / particle->mass;
        particle->integrate(dt, IntegrationType::Symplectic_Euler);
        //particleSystem.update(dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {
        create_generator<WindForceGenerator>(1);
    }

    void cleanup() override
    {

    }


     //template<typename TipoGenerador,typename... ArgumentoCorrespondiente>
     //requires std::is_base_of_v<ForceGenerator,TipoGenerador>
     //TipoGenerador create_generator(ArgumentoCorrespondiente... args) 
     //{
     //    return TipoGenerador(std::forward<ArgumentoCorrespondiente>(args)...);
     //}


     
     

private:
    std::vector<Particle*> particles;
    Particle* particle = nullptr;
    Force particleForce;
    GravityForceGenerator* gravityGenerator = nullptr;
    WindForceGenerator* wind = nullptr;

};
