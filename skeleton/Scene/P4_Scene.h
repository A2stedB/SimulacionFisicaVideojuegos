#pragma once
#include "Scene.h"
#include "Particle.h"
#include "ForceGenerator.h"
#include "Helper.h"
#include "ParticleSystem.h"
#include "Distribution.h"
#include "Particle.h"

class P4_Scene : public Scene
{
public:
    explicit P4_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        Particle* p1 = new Particle(shape,Position(10,0,0),BLUE);
        p1->mass = 1;

        Particle* p2 = new Particle(shape, Position(-11, 0, 0), BLUE);
        p1->mass = 2;

        SpringForceGenerator* f1 = new SpringForceGenerator(0.1,10,p1);
        SpringForceGenerator* f2 = new SpringForceGenerator(0.1,10,p2);

        force_generators.push_back(f1);
        force_generators.push_back(f2);

        particles.push_back(p1);
        particles.push_back(p2);
        forces.push_back(Force());
        forces.push_back(Force());

        //p = new Particle(shape, Position(0, 10, 0), RED);
        //p->mass = 1000;
    }

    void update(double dt) override
    {
        ResetForce();

        for (int i = 0; i < particles.size();++i)
        {
            Particle* particle = particles[i];

            for (int j = 0; j < force_generators.size();++j)
            {
                ForceGenerator* generator = force_generators[j];

                forces[i] += generator->AddForce(*particle, dt);
            }

            particle->acceleration = forces[i] / particle->mass;
            particle->Integrate(dt, IntegrationType::Symplectic_Euler);
        }

        //for (Particle* p : particles)
        //{

        //}
        //for (ForceGenerator* generator : force_generators)
        //{
        //    particle_force += generator->AddForce(*p,dt);
        //}

        //p->acceleration = particle_force / p->mass;
        //p->Integrate(dt, IntegrationType::Symplectic_Euler);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {

    }

    void cleanup() override
    {

    }




private:
    void ResetForce()
    {
        for (Force& force : forces)
        {
            force = Force(0, 0, 0);
        }
    }

    std::vector<ForceGenerator*> force_generators{};
    std::vector<Particle*> particles{};
    std::vector<Force> forces{};
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
};
