#pragma once
#include "../Vector3D.h"
#include "IntegrationType.h"
#include "../Helper.h"
namespace sim
{
    struct Particle
    {
        Particle(Position position, Velocity velocity = Velocity(), Acceleration acceleration = Acceleration());

        Position position{};
        Velocity velocity{};
        Acceleration acceleration{};
        //float mass{};
    };

    void Particle_Integrate(Ref<Particle> particle, double dt, IntegrationType integration_type);
}