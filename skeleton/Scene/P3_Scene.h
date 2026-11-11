#pragma once
#include "Scene.h"
#include "Particle.h"
#include "ForceGenerator.h"
#include "Helper.h"
#include "ParticleSystem.h"
#include "Distribution.h"
#include "Particle.h"

class P3_Scene : public Scene
{
public:
    explicit P3_Scene(std::string name) : Scene(std::move(name)) {};

    void init() override
    {
        ParticleSystem* first = new ParticleSystem();
        particle_systems.push_back(first);

        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
        ParticleModel model{ Velocity{1,-1,1},RED,Acceleration{0,0,0},shape,1,1000};

        ParticleGenerator* generator = new ParticleGenerator(Position{ 0,0,0 }, model,Max(10000));

        generator->generate_particle = [](Vector3D* position, Vector3D* velocity,int* lifetime)
            {
                int OFFSET = 30;

                position->x = distribution::uniform(position->x - OFFSET, position->x + OFFSET);
                position->y = distribution::uniform(position->y - OFFSET, position->y + OFFSET);
                position->z = distribution::uniform(position->z - OFFSET, position->z + OFFSET);

                velocity->x = distribution::normal(velocity->x, 3);
                velocity->y = distribution::normal(velocity->y, 3);
                velocity->z = distribution::normal(velocity->z, 3);

                *lifetime = distribution::normal(7000, 1000);
            };

        generator->random_generation_interval = [](float* next_generation_time)
            {
                *next_generation_time = distribution::uniform(0,0.1);
            };

        first->addGenerator(generator);

        ParticleModel model2{ Velocity{0,-10,0},YELLOW,Acceleration{0,-10,0},shape,5000 };

        //ParticleGenerator* generator2 = new ParticleGenerator(Position{ 20,20,-10 }, model2,Max(5000));
        //generator2->generate_particle = [](Vector3D* position, Vector3D* velocity, int* lifetime)
        //    {
        //        int offset = 20;
        //        position->x = distribution::normal(position->x - offset, position->x + offset);
        //        //position->y = distribution::normal(position->y,20);
        //        position->z = distribution::normal(position->z - offset, position->z + offset);

        //        //velocity->y = distribution::uniform(velocity->y - 5, velocity->y + 5);
        //    };

        ////first->addGenerator(generator2);

        //ParticleModel model3{ Velocity{0,20,0},BLUE,Acceleration{0,-10,0},shape,5000 };
        //ParticleGenerator* generator3 = new ParticleGenerator(Position{ 50,50,-20 }, model3, Max(1000));

        //generator3->generate_particle = [](Vector3D* position, Vector3D* velocity, int* lifetime)
        //    {
        //        velocity->x = distribution::uniform(-10, 10);
        //    };

        //first->addGenerator(generator3);

        BoxVolume box = { Position(20,0,0),50,50,50 };
        BoxVolume box2 = { Position(0,0,0),100,50,100 };

        gravity = new GravityForceGenerator();
        force_generators.push_back(gravity);
        gravity->Toggle();

        wind = new WindForceGenerator(Velocity(100, 0, 0), box);
        force_generators.push_back(wind);
        wind->Toggle();

        whirwind = new WhirlwindForceGenerator(box2);
        force_generators.push_back(whirwind);
        whirwind->Toggle();

        explosive = new ExplosiveForceGenerator(Position(0, 0, 0), 100, 1000000, 2);
        force_generators.push_back(explosive);
        explosive->Toggle();

        force_system_matrix = std::vector<std::vector<bool>>(force_generators.size(), std::vector<bool>(particle_systems.size(), true));

        first->PreCompute();
    }

    void update(double dt) override
    {
        for (ParticleSystem* particle_system : particle_systems)
        {
            particle_system->ResetForce();
        }

        for (int i = 0; i < force_generators.size(); ++i)
        {
            ForceGenerator* force_generator = force_generators[i];

            for (int j = 0; j < particle_systems.size(); ++j)
            {
                ParticleSystem* particle_system = particle_systems[j];
                if (force_system_matrix[i][j])
                {
                    for (int k = 0; k < particle_system->particles.size();++k)
                    {
                        Force& particle_force = particle_system->particle_force[k];
                        Particle* particle = particle_system->particles[k];
                        particle_force += force_generator->AddForce(*particle, dt);
                    }
                }
            }
        }

        for (ParticleSystem* particle_system : particle_systems)
        {
            particle_system->update(dt);
        }

        for (auto& proyectile : proyectiles)
        {
            proyectile->Integrate(dt, IntegrationType::Symplectic_Euler);
            //--proyectile->lifetime;

            //if (proyectile->lifetime <= 0)
            //{
            //    std::swap(proyectile, proyectiles[proyectiles.size() - 1]);
            //    delete proyectile;
            //    proyectiles.pop_back();
            //}
        };
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override
    {
        switch (key)
        {
            case 'z':
                gravity->Toggle();
                break;
            case 'x':
                wind->Toggle();
                break;
            case 'c':
                whirwind->Toggle();
                break;
            case 'v':
                explosive->Toggle();
                break;

            case 'k':
                explosive->ActiveExplosion();
                break;
            case 'f': {
                Proyectile* proyectile1 = new Proyectile(shape, GetCamera(), 100_m_s, -9.8_m_s, 100_g, 25_m_s, Color{ 0,1,0,1 });
                shape->acquireReference();
                proyectiles.push_back(proyectile1);
                //proyectile1->lifetime = 500;
                break;
            }
            case 'j': {
                Proyectile * proyectile2 = new Proyectile(shape, GetCamera(), 300_m_s, -9.8_m_s, 8_g, 25_m_s, Color{ 0,0,1,1 });
                shape->acquireReference();
                proyectiles.push_back(proyectile2);
                //proyectile2->lifetime = 500;
                break;
            }
            case '1':
                break;
            default:
                break;
        }
    }

    void cleanup() override
    {
        for (Particle* particle : proyectiles)
        {
            if (particle)
            {
                delete particle;
                particle = nullptr;
            }
        }
    }

     
     

private:
    std::vector<std::vector<bool>> force_system_matrix;
    std::vector<ParticleSystem*> particle_systems;
    std::vector<ForceGenerator*> force_generators;

    GravityForceGenerator* gravity = nullptr;
    WindForceGenerator* wind = nullptr;
    WhirlwindForceGenerator* whirwind = nullptr;
    ExplosiveForceGenerator* explosive = nullptr;

    std::vector<Particle*> proyectiles{};
    physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
};
