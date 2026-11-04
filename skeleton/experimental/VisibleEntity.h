#pragma once
#include "RenderUtils.hpp"
#include "ParticleExperimental.h"

struct Particle2
{
    Particle2(physx::PxShape* shape);

    sim::Particle particle;
    RenderItem* renderItem;
};