#pragma once
//#include "../Vector3D.h"
//#include "IntegrationType.h"
//#include "../Helper.h"
#include "Vector3D.h"
#include "core.h"

namespace sim
{
    struct Particle
    {
        struct Data
        {
            Position position{};
            Velocity velocity{};
            Acceleration acceleration{};
        };
        Particle() = default;
        Particle(Position position, Velocity velocity = Velocity(), Acceleration acceleration = Acceleration());
        Particle(Data data);

        Position position{};
        Velocity velocity{};
        Acceleration acceleration{};
        //float mass{};
    };

    struct ParticleWithMass 
    {
        struct Data
        {
            Particle::Data particle_data{};
            float mass = 1; // Para no tener un NaN
        };


        ParticleWithMass() = default;
        ParticleWithMass(Data data);

        Particle particle;
        float mass;
    };
}

namespace sim
{
    void Particle_Integrate(Pointer<Particle> particle, double dt, IntegrateType integration_type);
}

using Projectile = sim::ParticleWithMass;

Projectile create_projectile(sim::ParticleWithMass::Data data);