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
        struct ParticleData
        {
            Position position{};
            Velocity velocity{};
            Acceleration acceleration{};
        };
        Particle(Position position, Velocity velocity = Velocity(), Acceleration acceleration = Acceleration());
        Particle(ParticleData data);

        Position position{};
        Velocity velocity{};
        Acceleration acceleration{};
        //float mass{};
    };

    struct ParticleWithMass 
    {
        struct ParticleWithMassData
        {
            Particle::ParticleData particle_data{};
            float mass = 1; // Para no tener un NaN
        };

        ParticleWithMass(ParticleWithMassData data);

        Particle particle;
        float mass;
    };

    using Projectile = ParticleWithMass;
}

namespace sim
{
    void Particle_Integrate(Pointer<Particle> particle, double dt, IntegrateType integration_type);
}